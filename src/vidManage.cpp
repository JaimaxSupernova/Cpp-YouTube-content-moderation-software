#include "vidManage.h"

struct Video {
    //string v_id;
    string v_name;
    //string v_length;
    //int likes;
    //int dislikes;
    string creator;
    double l_dl_ratio;
};
bool compareLikes(const Video& r1, const Video& r2)
{
    return r1.l_dl_ratio < r2.l_dl_ratio;
}
bool compareScores(const Channel& c1, const Channel& c2)
{
    return c1.score < c2.score;
}

Videos::Videos(const string &vidfile)
{
VideoFile=vidfile;
string line;
ifstream file(VideoFile);
    if (!file.is_open())
    {
        cout << "videos file cannot be opened.\n";
    }
    while (getline(file, line))
    {
        istringstream iss(line);
        vector<string> videoData;

        // Read each column directly from the stringstream
        string column;
        while (getline(iss, column, ','))
        {
            videoData.push_back(column);
        }

        // Add the video data to the videos vector
        videos.push_back(videoData);
    }

    file.close();
}



void Videos::getVideo(const int &vidNum)
{
    bool checked = false;
    for (size_t i = 1; i <= 100; i++)
    {
        if (i == vidNum && !checked) {
            chosenVideo = vQueue.front();
            cout << "Selected Video: " << chosenVideo.second.first << " By: " << chosenVideo.second.second << endl;
            break;
        }
        else if (!checked){
            vQueue.pop();
        }
    }
    
    queue<pair<string, pair<string, string>>> empty;
    swap(vQueue, empty);    
}

void Videos::addVideo(const string &channelName, const string &vidName, const string &videoDuration)
{
    int linecount = 0;
    vector<string> newvideo;
    string videoid;
    for (vector<string>& videoData : videos) {
        linecount++;
    }
    videoid = "video_" + to_string(linecount+1);
    newvideo.push_back(videoid);
    newvideo.push_back(vidName);
    newvideo.push_back(videoDuration);
    newvideo.push_back("0");
    newvideo.push_back("0");
    newvideo.push_back(channelName);
    videos.push_back(newvideo);
    updateFile();
    cout<<"video created!"<<endl;
}

void Videos::renameVideo(const int &vidNum, const string &newname)
{
    map <string,string> videomap;
    string vidkey;
    getVideo(vidNum);
    for (const vector<string>& videoData : videos) {
        if (chosenVideo.first == videoData[0])
        {
            vidkey = videoData[0];
            videomap[vidkey] = videoData[1];
        }
    }

    for (vector<string>& videoData : videos) {
        if (videomap.find(videoData[0]) != videomap.end())
        {
            videoData[1]=newname;
        }
    }
    updateFile();
    cout<<"Video renamed to: "<< newname <<endl;
}



void Videos::deleteVideo(const int &videoNum)
{
    map <string,string> videomap;
    string vidkey;
    int count=0;
    getVideo(videoNum);
    for (vector<string>& videoData : videos) {
        if (chosenVideo.first == videoData[0])
        {
            videos.erase(videos.begin() + count);
        }else{
            count++;
        }
    }

    updateFile();
    cout<< "Video Deleted! " <<endl;
}

void Videos::getcreatorchannel(const string &channelName)
{
    int count = 1;
    cout << "Videos by: " << channelName << endl;
    // Find videos that match the keyword
    for (const vector<string>& videoData : videos) {
        if (videoData[5].find(channelName) != string::npos) {
            // Add video and channel information to the queue
            vQueue.push(make_pair(videoData[0], make_pair(videoData[1],videoData[5] )));
            cout << count <<": " << videoData[1] << " By: " << videoData[5] << endl;
            count ++;
        }
    }
}

void Videos::resetLikedislike(const int &vidnumber)
{
        map <string,string> videomap;
    string vidkey;
    getVideo(vidnumber);
    for (vector<string>& videoData : videos) {
        if (chosenVideo.first == videoData[0])
        {
            videoData[3] = "0";
            videoData[4] = "0";
        }
    }

    updateFile();
    cout<< "Likes and Dislikes reset!" <<endl;
}

vector<string> Videos::getKeywordVideos(const string& keyword) {
    vector<string> vidkey;
    int count = 1;
    cout << "Videos related to: " << keyword << endl;
    // Find videos that match the keyword
    for (const vector<string>& videoData : videos) {
        if (videoData[1].find(keyword) != string::npos) {
            // Add video and channel information to the queue
            vQueue.push(make_pair(videoData[0], make_pair(videoData[1],videoData[5] )));
            cout << count <<": " << videoData[1] << " By: " << videoData[5] << endl;
            count ++;
        if (count > 20)
        {
            break;
        }
        }
    }
    return vidkey;
}

void Videos::getKeywordReccomendation(const string &keyword)
{
    vector<Video> videoslike;
    list<Video> videoslikelist;
    pair<string, pair<string, string>> thisV;
    
    Video vd;
    cout << "Top videos related to: " << keyword << endl;
    int count = 1;
    for (vector<string>& videoData : videos) {
        if (videoData[1].find(keyword) != string::npos) {
            vd.l_dl_ratio = stoi(videoData[3])/stoi(videoData[4]); 
            vd.creator = videoData[5];
            vd.v_name = videoData[1];
            videoslike.push_back(vd);
            thisV.first = videoData[0];
            thisV.second.first = videoData[1];
            thisV.second.second = videoData[5];
        }
    }
    sort(videoslike.rbegin(), videoslike.rend(), compareLikes);
        for (Video vd : videoslike) {
            videoslikelist.push_back(vd);
        }
        for (Video vd : videoslikelist) {
            cout << count << ": " << vd.v_name << " By: " << vd.creator  << endl;
            count++;
            
            vQueue.push(thisV);
            if (count > 10) {
                break;
            }
        }
}


void Videos::getTrendChannels()
{
    Creator p;
    string textfile = "users.txt";
    string line;
    int space;
    int lastspace;
    string username;
    int count = 1;
    vector<Channel> scores;
    ifstream userfile(textfile);
    Channel c;
    if (!userfile.is_open()) {
        cout << "users file cannot be opened.\n";
    }
    while (getline(userfile, line)){
        if (line.find("-") != string::npos) {}else{
            space =line.find(" ");
            lastspace = line.find_last_of(" ");
            username= line.substr(space+1, lastspace-space);
            username=username.substr(0,username.length()-1);
            c.score = p.getChannelScore(username);
            c.c_name = username;
            scores.push_back(c);
        }
    }
    sort(scores.rbegin(), scores.rend(), compareScores);
    cout<<"Top 10 trending channels:\n";
    for (Channel c : scores)
    {
        scoresDeque.push_back(c);
    }
    
    for (Channel c : scoresDeque){
        cout<<count<<"-"<<c.c_name<<endl;
        count++;
        
        if (count > 10)
        {
            break;
        }
    }
}

void Videos::updateLikeDislike(const string &rating)
{
    for (vector<string>& videoData : videos) {
        if (videoData[0]==chosenVideo.first) {
            if (rating == "l")
            {
                videoData[3]=to_string(stoi(videoData[3])+1);
                cout<<"video like count updated, new like count is "<< videoData[3]<<endl;
            }else if (rating == "dl")
            {
                videoData[4]=to_string(stoi(videoData[4])+1);
                cout<<"video disliked"<<endl;
            }
        }
    }
    updateFile();
}

void Videos::getChannel(const int &Channelnum){
    vector<string> vidkey;
    int count = 1;
    string channelName;
    for (size_t i = 1; i <= 10; i++)
    {
        if (i == Channelnum) {
            chosenChannel = scoresDeque.front();
            cout << "Selected Channel: " << chosenChannel.c_name << endl;
    }else{
            scoresDeque.pop_front();
        }
    }
    scoresDeque.clear();
    cout << "Videos by: " << chosenChannel.c_name << endl;
    // Find videos that match the keyword
    for (const vector<string>& videoData : videos) {
        if (videoData[5].find(chosenChannel.c_name) != string::npos) {
            // Add video and channel information to the queue
            vQueue.push(make_pair(videoData[0], make_pair(videoData[1],videoData[5] )));
            cout << count <<": " << videoData[1] << " By: " << videoData[5] << endl;
            count ++;
        }
    }
}

void Videos::updateFile()
{
    ofstream file (VideoFile);
    if (file.is_open())
    {
        for (const vector<string> &videoData : videos) {
            file << videoData[0]<<","<<videoData[1]<<","<<videoData[2]<<","<<videoData[3]<<","<<videoData[4]<<","<<videoData[5]<<endl;
        }
        file.close();
    }else cout << "Unable to open file";
}

