#include <cstdlib>

#include <iostream>
#include <fstream>


int main(int argc, char **argv){
    if(argc < 3){
        std::cerr << "Lack of arguments !" << std::endl;
        std::cerr << "Correct Format: ./objgen.exe conf_file task_file obj_file" << std::endl;
        std::cerr << "Please check your input carefully !" << std::endl << std::endl;
        exit(-1);
    }
    std::ifstream infile_conf(argv[1]);
    std::ifstream infile_task(argv[2]);
    std::ofstream outfile(argv[3]);

    std::string line;
    while(getline(infile_conf, line)) {
        outfile << line << std::endl;
    }
    outfile << std::endl;

    while(getline(infile_task, line)) {
        outfile << line << std::endl;
    }
    outfile << std::endl;

    outfile << "EOF";

    return 0;
}
