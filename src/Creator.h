// include your own comments

// NOTE THIS CLASS IN INCOMPLETE, YOU SHOULD AIM TO COMPLETE ITS DEFINITION

#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "Person.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

class NoScoreException: public exception
{
};

class Creator: public Person
{   public:
       // constructor should initialise name and registration number using arguments
       Creator(const string &channel_name, int regNo);

	   // method to return registration number
	   int getRegNo() const;

	   // method to add the score to the map
	   // this method should be handy when updating the multimap
	   void addScore(float score,string video_name);

	   // method to update the accumulative score map
	   // should throw NoRatioException if creator has no videos yet
	   bool updateLikeDislikeRatio();

	   double getChannelScore(string Channelname);

		Creator(){}
    private:
	   int regNo;
	   string channel_name;
	   multimap<string,float> videos_and_ratios;  // scores map, having the video_name and its ratio
	   float like_dislike_ratio_total; // overall channel score 

	// friend function to output details of creator to stream
    // output to be defined and formated by you
    // if the creator has no videos "has no videos" should be output instead of displaying the videos
    friend ostream& operator<<(ostream &str, const Creator &s);
};

#endif
