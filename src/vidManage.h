#include <vector>
#include <fstream>
#include <stdexcept>
#include <queue>
#include <iostream>
#include <sstream>
#include <iterator>
#include <list>
#include <algorithm>
#include <regex>
#include "Creator.h"

using namespace std;
    struct Channel{
    double score;
    string c_name;   
    };    
class Videos {
public:
    Videos(const string &vidfile);

    void getVideo(const int &vidNum);

    void addVideo(const string &channelName, const string &vidName, const string &videoDuration);

    void renameVideo(const int &vidNum, const string &newname);

    void deleteVideo(const int &videoNum);

    void getcreatorchannel(const string &channelName);

    vector<string> getKeywordVideos(const string& keyword);

    void getKeywordReccomendation(const string& keyword);

    void getTrendChannels();

    void resetLikedislike(const int& vidnumber);

    void updateLikeDislike( const string& rating);

    void getChannel(const int &channelNum);

    void updateFile();
    
    

private:
    vector<vector<string>> videos;
    string VideoFile;
    queue<pair<string, pair<string, string>>> vQueue;
    pair<string, pair<string, string>> chosenVideo;
    Channel chosenChannel;
    deque<Channel> scoresDeque;
};

