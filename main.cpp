#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <opencv2/opencv.hpp>
#include "crowdsight.h"
//#include <boost/tokenizer.hpp>
#define CSV_IO_NO_THREAD
#include "csv.h"

using namespace std;
using namespace cv;
//using namespace boost;


int main() {

    CrowdSight* crowdsight;

    string license = "f187f8d8b27f424fbab9064c18a7e0e4";
    string datadir = "/usr/local/crowdsight/data/";


    crowdsight = new CrowdSight(datadir, DEVELOPER);

    if (!crowdsight->authenticate(license)) {
        delete crowdsight;
        crowdsight = NULL;
    }


    namedWindow("Test", CV_WINDOW_AUTOSIZE);

    // Read frame from file
    vector<string> filenames;
    vector<double> real_min_ages;
    vector<int> crowdsight_ages;


    string data("8.txt");

    io::CSVReader<4> in("8.txt");
    string uid;
    string filename;
    string age;
    string gender;



    ofstream crowdsight_file("./crowdsight_8.txt");
    crowdsight_file.is_open();
    Mat frame;

    while(in.read_row(uid,filename, age, gender)) {
        cout << filename << endl;


        frame = imread(filename);

        if (!crowdsight->process(frame)) {
            std::cerr << "Failed to process frame: " << crowdsight->getErrorDescription() << std::endl;

        }



        std::vector<Person> people;
        crowdsight->getCurrentPeople(people);

        if (people.size() > 0)
        {
            std::vector<Person>::iterator it;

            for (it = people.begin(); it < people.end(); it++) {

                cout << it->getAge() << endl;
                crowdsight_file << uid << ",";
                crowdsight_file << filename << ",";
                crowdsight_file << age << ",";
                crowdsight_file << gender << ",";
                crowdsight_file << to_string(it->getAge()) << endl;

            }

        }

    }

    crowdsight_file.close();
    return 0;
}