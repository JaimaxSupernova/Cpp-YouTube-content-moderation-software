#include "Person.h"
#include "Creator.h"
#include "User.h"
#include "vidManage.h"
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <iostream>

int main()
{

    string loginName, line, keyword, choice2, vidName, vidDuration;
    vector<string> keynum;
    bool foundUser = false, foundCreator = false, valid = false, valid2 = false, valid3 = false;
    string textfile = "users.txt";
    string videoFile = "fake_youtube_data_updated.txt";
    int endRegPos, startScorePos, choice, lastReg, regNo, choice3;
    double channelScore;
    fstream f;
    Videos *v = new Videos(videoFile);

    ifstream userfile1(textfile);
    if (!userfile1.is_open())
    {
        cout << "users file cannot be opened.\n";
        return 1;
    }
    while (getline(userfile1, line))
    {
        endRegPos = line.find(" ");
        lastReg = stoi(line.substr(0, endRegPos));
    }
    userfile1.close();
    cout << "Login\n" << endl;
    cout << "Username:" << endl;
    getline(cin, loginName);

    ifstream userfile(textfile);
    while (getline(userfile, line))
    {
        if (line.find(loginName) != string::npos)
        {
            if (line.find("-") != string::npos)
            {
                foundUser = true;
                endRegPos = line.find(" ");
                regNo = stoi(line.substr(0, endRegPos));
            isuser:
                User *p = new User(loginName, regNo);

                cout << "Logged in as user: " << loginName << endl;
                userfile.close();
                while (1)
                {
                    cout << "\nPlease select a number for the option of:\n"<< endl;
                    cout << "    1- Get video\n    2- Get video recommendations\n    3- Trending channels\n    4- Exit\n" << endl;
                    cout << "Option: ";
                    cin >> choice;
                    cin.ignore();
                    switch (choice)
                    {
                    case 1:
                    {
                        cout << "Enter keyword: ";
                        cin >> keyword;
                        cin.ignore();
                        keynum = v->getKeywordVideos(keyword);
                        while (!valid)
                        {
                            cout << "Would you like to choose a video? If not you will return to menu" << endl;
                            getline(cin, choice2);
                            if (choice2 == "yes")
                            {
                                while (!valid3)
                                {
                                    cout << "Which video would you like to watch?" << endl;
                                    getline(cin, choice2);
                                    v->getVideo(stoi(choice2));
                                    if (stoi(choice2) <= 20 || stoi(choice2) > 0)
                                    {
                                        valid3 = true;
                                    }
                                    else
                                    {
                                        cout << "enter a valid number" << endl;
                                    }
                                }
                                valid3 = false;
                                while (!valid2)
                                {
                                    cout << "how was the video?\n1- good\n2- bad" << endl;
                                    cin >> choice;
                                    cin.ignore();
                                    switch (choice)
                                    {
                                    case 1:
                                        v->updateLikeDislike("l");
                                        valid2 = true;
                                        valid = true;
                                        break;
                                    case 2:
                                        v->updateLikeDislike("dl");
                                        valid2 = true;
                                        valid = true;
                                        break;

                                    default:
                                        cout << "invalid entry, please choose again\n";
                                        break;
                                    }
                                }
                                valid2 = false;
                            }
                            else if (choice2 == "no")
                            {
                                break;
                            }
                            else
                            {
                                cout << "Invalid entry, please try again" << endl;
                            }
                        }
                        valid = false;
                        break;
                    }
                    case 2:
                    {
                        cout << "Enter keyword: ";
                        cin >> keyword;
                        cin.ignore();
                        v->getKeywordReccomendation(keyword);
                        while (!valid)
                        {
                            cout << "Would you like to choose a video? If not you will return to menu" << endl;
                            getline(cin, choice2);
                            if (choice2 == "yes")
                            {
                                while (!valid3)
                                {
                                    cout << "Which video would you like to watch?\n\nvideo number:" << endl;
                                    getline(cin, choice2);
                                    v->getVideo(stoi(choice2));
                                    if (stoi(choice2) <= 10)
                                    {
                                        valid3 = true;
                                    }
                                    else
                                    {
                                        cout << "enter a valid number" << endl;
                                    }
                                }
                                valid3 = false;
                                while (!valid2)
                                {
                                    cout << "how was the video?\n1- good\n2- bad" << endl;
                                    cin >> choice;
                                    cin.ignore();
                                    switch (choice)
                                    {
                                    case 1:
                                        v->updateLikeDislike("l");
                                        valid2 = true;
                                        valid = true;
                                        break;
                                    case 2:
                                        v->updateLikeDislike("dl");
                                        valid2 = true;
                                        valid = true;
                                        break;

                                    default:
                                        cout << "invalid entry, please choose again\n";
                                        break;
                                    }
                                }
                                valid2 = false;
                            }
                            else if (choice2 == "no")
                            {
                                break;
                            }
                            else
                            {
                                cout << "Invalid entry, please try again" << endl;
                            }
                        }
                        valid = false;
                        break;
                    }
                    case 3:
                    {
                        v->getTrendChannels();
                        while (!valid3)
                        {
                            cout << "Which channel would you like to explore?\n\nEnter channel number: " << endl;
                            getline(cin, choice2);
                            if (stoi(choice2) <= 10)
                            {
                                v->getChannel(stoi(choice2));
                                valid3 = true;
                            }
                            else
                            {
                                cout << "enter a valid number" << endl;
                            }
                        }
                        valid3 = false;

                        while (!valid)
                        {
                            cout << "Would you like to choose a video? If not you will return to menu" << endl;
                            getline(cin, choice2);
                            if (choice2 == "yes")
                            {
                                while (!valid3)
                                {
                                    cout << "Which video would you like to watch?\n\nMovie Number:" << endl;
                                    getline(cin, choice2);
                                    v->getVideo(stoi(choice2));
                                    valid3 = true;
                                    cout << "enter a valid number" << endl;
                                }
                                valid3 = false;
                                while (!valid2)
                                {
                                    cout << "how was the video?\n1- good\n2- bad" << endl;
                                    cin >> choice;
                                    cin.ignore();
                                    switch (choice)
                                    {
                                    case 1:
                                        v->updateLikeDislike("l");
                                        valid2 = true;
                                        valid = true;
                                        break;
                                    case 2:
                                        v->updateLikeDislike("dl");
                                        valid2 = true;
                                        valid = true;
                                        break;

                                    default:
                                        cout << "invalid entry, please choose again\n";
                                        break;
                                    }
                                }
                                valid2 = false;
                            }
                            else if (choice2 == "no")
                            {
                                break;
                            }
                            else
                            {
                                cout << "Invalid entry, please try again" << endl;
                            }
                        }
                        valid = false;
                        break;
                    }
                    case 4:
                    {
                        cout << "program exited successfully.\n";
                        return 0;
                    }
                    }
                }
            }
            else
            {
                foundCreator = true;
                endRegPos = line.find(" ");
                regNo = stoi(line.substr(0, endRegPos));
                startScorePos = line.find_last_of(" ");
                channelScore = stod(line.substr(startScorePos + 1));
            iscreator:
                Creator *p = new Creator(loginName, regNo);
                cout << "Logged in as creator: " << loginName << endl;
                userfile.close();
                while (1)
                {

                    cout << "\nPlease select a number for the option of:\n" << endl;
                    cout << "    1- Show channel score\n    2- Create a video\n    3- Manage a video\n    4- Exit\n" << endl;
                    cout << "Option: ";
                    cin >> choice;
                    cin.ignore();
                    switch (choice)
                    {
                    case 1:
                    {
                        cout << "Your channel score is: " << p->getChannelScore(loginName);
                        break;
                    }
                    case 2:
                    {
                        cout << "You are making a video" << endl;
                        cout << "Enter name of video: ";
                        getline(cin, vidName);
                        cout << "Enter length of video in format mins:secs :  ";
                        getline(cin, vidDuration);
                        v->addVideo(loginName, vidName, vidDuration);
                        break;
                    }
                    case 3:
                    {
                        cout << "listing all your videos..."<<endl;
                        v->getcreatorchannel(loginName);
                        while (!valid)
                        {
                            cout<<"would you like to:\n1-rename a video\n2-reset likes/dislikes\n3-delete a video\n4-Exit"<<endl;
                            cin >> choice;
                            cin.ignore();
                            if (choice == 4)
                            {
                                break;
                            }
                            
                            cout<<"choose a video number to edit: ";
                            cin >> choice3;
                            cin.ignore();
                            switch (choice)
                            {
                            case 1:
                                cout<<"what would you like to rename the video to? "<<endl;
                                getline(cin,choice2);
                                v->renameVideo(choice3, choice2);
                                break;
                            case 2:
                                cout<<"choose a video whose likes/dislikes you want to reset: ";
                                getline(cin,choice2);
                                v->resetLikedislike(choice3);
                                break;
                            case 3:
                                v->deleteVideo(choice3);
                                break;

                            default:
                                cout << "invalid entry"<<endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 4:
                    {
                        cout << "program exited successfully.\n";
                        return 0;
                    }
                    default:
                    {
                        cout << "Invalid option, please try again\n";
                    }
                    }
                }
            }
            break;
        }
    }
    if (!foundUser && !foundCreator)
    {
        userfile.close();
        regNo = (lastReg + 1);
        f.open(textfile, ios::app);
        cout << "Username not found, please create a new profile" << endl;
        cout << "Which of the following best describes you:" << endl;
        cout << "1- User\n2- Creator" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            f << (lastReg + 1) << " " << loginName << " -\n";
            User *p = new User(loginName, (lastReg + 1));
            foundUser = true;
            userfile.close();
            goto isuser;
        }
        case 2:
        {
            f << (lastReg + 1) << " " << loginName << " 0.0\n";
            Creator *p = new Creator(loginName, regNo);
            foundCreator = true;
            userfile.close();
            goto iscreator;
        }
        default:
        {
            cout << "Invalid option, please try again\n";
        }
        }
    }
    delete v;
    return 0;
}
