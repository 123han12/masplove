#include <iostream>
#include <yaml-cpp/yaml.h>
 
using namespace std;
 
int main()
{
    YAML::Node config = YAML::LoadFile("./config.yaml");
    vector<string> illegal_rules = config["illegal_rules"].as<vector<string>>();
    cout << illegal_rules.size() << endl;
    for (const string s : illegal_rules) {
        cout << s << endl;
    }
    
    return 0;
}