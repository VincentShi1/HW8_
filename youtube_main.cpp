#include <iostream>
#include <functional>
#include <string.h>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <regex>
#include <list>
#include <vector>
#include "commentTree.h"
#include <unordered_map>


std::ostream& printLine(std::unordered_map<std::string, TreeNode*> tree, std::ostream& out, int depth, std::string cID);

void inputCommand(std::unordered_map<std::string, TreeNode*>& tree, std::string command, std::string parent_id, std::string id, std::string user, std::string comment, std::ostream& out);
//store value into hash map :) 


//void function that takes in a string and an unordered map (hash map) to store the lines from json file
// designed to inserting json file into the hash map and has an ordered vec to keep track of order.
void makeJson(std::string json_content, std::unordered_map<std::string, TreeNode*> &tree, std::vector<std::string>& orderVec) {
    //std::cout << "Test1" << std::endl;
    std::string vid_id = json_content.substr(json_content.find("video_id")+12, 11);
    std::string auth = json_content.substr(json_content.find("author")+10, (json_content.find(",", json_content.find("author"))) - (json_content.find("author")+11));
    std::string cID = json_content.substr(json_content.find("comment_id")+14, (json_content.find(",", json_content.find("comment_id"))) - (json_content.find("comment_id")+15));
    int likeCount = stoi(json_content.substr(json_content.find("like_count")+13, (json_content.find(",", json_content.find("like_count"))) - (json_content.find("like_count")+13)));
    int replyCount = stoi(json_content.substr(json_content.find("reply_count")+14, (json_content.find(",", json_content.find("reply_count"))) - (json_content.find("reply_count")+14)));
    bool isReply = false;;
    std::string pID = json_content.substr(json_content.find("parent_comment_id")+21, (json_content.find(",", json_content.find("parent_comment_id"))) - (json_content.find("parent_comment_id")+22));
    std::string pDate = json_content.substr(json_content.find("published_date")+18 , (json_content.find(",", json_content.find("published_date"))) - (json_content.find("published_date")+19));
    std::string cDate = json_content.substr(json_content.find("crawled_date")+16, (json_content.find(",", json_content.find("crawled_date"))) - (json_content.find("crawled_date")+17));
    bool isVidOwner = false;
    //std::string comment;
    // std::cout << json_content.length() << std::endl;
    //std::cout << json_content.find("comment\"") << std::endl;
    std::string comment = json_content.substr(json_content.find("comment\"") + 11, (json_content.rfind("}")) - (json_content.rfind("comment\"")+12));
    //std::string comment = json_content.substr(json_content.rfind("comment")+9);
    //std::string comment = json_content.substr(json_content.rfind("comment")+11, (json_content.rfind("}")) - (json_content.rfind("comment")+13));
    //std::cout << "COMMENT: " << comment << std::endl;

    std::string isReplyTemp = json_content.substr(json_content.find("is_reply")+11, (json_content.find(",", json_content.find("is_reply"))) - (json_content.find("is_reply")+12));
    std::string isVidOwnerTemp = json_content.substr(json_content.find("is_video_owner")+17, (json_content.find(",", json_content.find("is_video_owner"))) - (json_content.find("is_video_owner")+17));
    if(isReplyTemp == "True") {
        isReply = true;
    }
    else { 
        isReply = false;
    }

    if(isVidOwnerTemp == "True") {
        isVidOwner = true;
    }
    else { 
        isVidOwner = false;
    }

    //std::cout << "Test2" << std::endl;
    TreeNode* currNode = new TreeNode(vid_id, auth, cID, likeCount, replyCount, isReply, pID, pDate, cDate, isVidOwner, comment);
    tree[cID] = currNode;
    orderVec.push_back(cID);
    // shelly was here 

}

void makeInput(std::string fullLine, std::unordered_map<std::string, TreeNode*> &tree, std::ostream& out) {
    std::string command;
    std::string pID;
    std::string id;
    std::string author;
    std::string comment;

    if(fullLine.find("reply_to_video") != std::string::npos) {
        command = "reply_to_video";

        std::string tempParam = "";
        std::vector<std::string> temp;
        for(char x : fullLine) {
            if(x == ' ') { 
                temp.push_back(tempParam);
                tempParam = "";
            }
            else { 
                tempParam = tempParam + x;
            }
        }
        temp.push_back(tempParam);

        id = temp[1];
        author = temp[3];
        for(int i = 4; i < temp.size(); i++) {
            comment += temp[i];
            if (i != temp.size() - 1) comment += ' ';
        }


        comment = comment.substr(1, comment.size()-2);
    }
    if(fullLine.find("reply_to_comment") != std::string::npos) {
        command = "reply_to_comment";

        std::string tempParam = "";
        std::vector<std::string> temp;
        for(char x : fullLine) {
            if(x == ' ') { 
                temp.push_back(tempParam);
                tempParam = "";
            }
            else { 
                tempParam = tempParam + x;
            }
        }
        temp.push_back(tempParam);

        pID = temp[1];
        id = temp[2];
        author = temp[3];
        for(int i = 4; i < temp.size(); i++) {
            comment += temp[i];
            if (i != temp.size() - 1) comment += ' ';
        }
        comment = comment.substr(1, comment.size()-2);

    }
    if(fullLine.find("like_comment") != std::string::npos) {
        command = "like_comment";

        std::string tempParam = "";
        std::vector<std::string> temp;
        for(char x : fullLine) {
            if(x == ' ') { 
                temp.push_back(tempParam);
                tempParam = "";
            }
            else { 
                tempParam = tempParam + x;
            }
        }
        temp.push_back(tempParam);

        // std::cout << "-----" << std::endl;
        // std::cout << fullLine << std::endl;
        // for (int i = 0; i < temp.size(); i++) {
        //     std::cout << temp[i] << std::endl;
        // }
        // std::cout << "-----" << std::endl;

        id = temp[1];

        //comment = comment.substr(1, comment.size()-2);
    }
    if(fullLine.find("delete_comment") != std::string::npos) {
        command = "delete_comment";
        id;

        std::string tempParam = "";
        std::vector<std::string> temp;
        for(char x : fullLine) {
            if(x == ' ') { 
                temp.push_back(tempParam);
                tempParam = "";
            }
            else { 
                tempParam = tempParam + x;
            }
        }
        temp.push_back(tempParam);

        id = temp[1];

        //comment = comment.substr(1, comment.size()-2);
    }

    if(fullLine.find("display_comment") != std::string::npos) {
        command = "display_comment";
        id;

        std::string tempParam = "";
        std::vector<std::string> temp;
        for(char x : fullLine) {
            if(x == ' ') { 
                temp.push_back(tempParam);
                tempParam = "";
            }
            else { 
                tempParam = tempParam + x;
            }
        }
        temp.push_back(tempParam);

        id = temp[1];
        //comment = comment.substr(1, comment.size()-2);
    } 
    std::cout << comment << std::endl;
    std::cout << author << std::endl;
    std::cout << pID << std::endl;
    std::cout << command << std::endl;
    std::cout << id << std::endl;
    
    inputCommand(tree, command, pID, id, author, comment, out);
}

//sort parent stuff :)))
//🤥🤥🤥🤥🤥🤥🤥🤥

//???? //must be here HMMM

//goes through the hash and search and check their pid, and 
void assignParent(std::unordered_map<std::string, TreeNode*>& tree, std::vector<std::string> orderVec) {
    std::unordered_map<std::string, TreeNode*> temp = tree;
    //search for PID ig :), since comment id is already being assigned as the key
    // for(std::unordered_map<std::string, TreeNode*>::iterator it = tree.begin(); it!= tree.end();it++) {
    //     for(std::unordered_map<std::string, TreeNode*>::iterator next = temp.begin(); next!= temp.end();next++) {
    //         if(it->first == next->second->getPID()) {
    //             it->second->children.push_back(next->second);
    //             //root -> children -> children -> etc. 
    //         }
            
    //     }
    // }

    //comment id == parent id 
    //store that treenode into the vector of the parent node

    
    for(int i = 0; i < orderVec.size(); i++) {
        for(int j = 0; j < orderVec.size(); j++) {
            if(orderVec[i] == tree.at(orderVec[j])->getPID()) {
                tree.at(orderVec[i])->children.push_back(tree.at(orderVec[j]));
                //root -> children -> children -> etc. 
            }
            
        }
    }


}

// void assignParent(std::unordered_map<std::string, TreeNode*>& tree) {
//     for (char& entry : tree) {
//         const std::string& parentCommentID = entry.second->getPID();

//         // Find the parent node using the parent comment ID
//         char parentIt = tree.find(parentCommentID);
//         if (parentIt != tree.end()) {
//             // Add the current node as a child of the parent node
//             parentIt->second->children.push_back(entry.second);
//         } else {
//             // Handle the case where the parent node is not found
//             // You may want to adjust this based on your specific requirements
//             std::cerr << "Error: Parent comment not found for " << entry.first << std::endl;
//         }
//     }
// }

void inputCommand(std::unordered_map<std::string, TreeNode*>& tree, std::string command, std::string parent_id, std::string id, std::string user, std::string comment, std::ostream& out) {
    if(command == "reply_to_video") {
        TreeNode* newVideo = new TreeNode(id, user ,comment);
        tree[id] = newVideo;
    }
    if(command == "reply_to_comment") {
        //std::cout <<"hELLO" << std::endl;
        TreeNode* newReply = new TreeNode(parent_id, id, user, comment);
        //std::cout << "wtf" << std::endl;

        tree[parent_id]->children.push_back(newReply); // why seg fault
        //does it not exist? 
        //std::cout << "wtf2" << std::endl;

        tree[id] = newReply;
        tree[parent_id]->addReplyCount();
        
    }
    if(command == "like_comment") {
        //std::cout << "test" << std::endl;
        //std::cout << id << std::endl;
        tree[id]->addLike();
        //std::cout << "work bitch" << std::endl;
    }
    //probably memory error
    if(command == "delete_comment") {
        std::string parentID = tree[id]->getPID();
        tree[id]->children.clear();
        tree.erase(id);
        std::cout << "helpppp" << std::endl;
        tree[parentID]->subtractReplyCount();
        std::cout << "WTF2" << std::endl;
    }
    if(command == "display_comment") {
        printLine(tree, out, 0, id);
    }
    
}



std::ostream& printLine(std::unordered_map<std::string, TreeNode*> tree, std::ostream& out, int depth, std::string cID) {
    int spaces = depth * 4;
    out << std::string(spaces, ' ') << tree[cID]->getAuth() <<" "<< tree[cID]->getPDate() <<std::endl;
    out << std::string(spaces, ' ') << tree[cID]->getComm() << std::endl;
    out << std::string(spaces, ' ') << "\U0001F44D" << " " << tree[cID]->getLike() << std::endl;

    if(tree[cID]->getReplyCount() == 1) {
        out << std::string(spaces, ' ') << tree[cID]->getReplyCount() << " reply" <<std::endl;
    }
    else if(tree[cID]->getReplyCount() > 1) {
        out << std::string(spaces, ' ') << tree[cID]->getReplyCount() << " replies" << std::endl;
    } 
    for(int i = 0; i < tree[cID]->children.size(); i++) {
        printLine(tree, out, depth + 1, tree[cID]->children[i]->getCID());
    }
    std::cout << "check" << std::endl;
    return out;
}

// std::ostream& printAll(std::unordered_map<std::string, TreeNode*> tree, std::ostream& out) {
//     for(auto &node : tree) {
//         std::cout << "check bich" << std::endl;
//         if(node.second->getPID() == "") {
//             std::cout << "check22" << std::endl;
//             printLine(tree, out, 0, node.second->getCID());
//         }
//     }
//     return out;
// }



int main(int argc, char* argv[]) {
    std::ifstream jsonFile(argv[1]);
    std::ifstream inputFile(argv[2]);
    std::ofstream outputFile(argv[3]);
    std::ofstream tempFile(argv[4]);
    if(!jsonFile.good()) {
        std::cerr << "Can't open " << argv[1] << "\n";
        return 1;
    }
    if(!inputFile.good()) {
        std::cerr << "Can't open " << argv[2] << "\n";
        return 1;
    }
    if(!outputFile.good()) {
        std::cerr << "Can't open " << argv[3] << "\n";
        return 1;
    }

    //hash
    std::unordered_map<std::string, TreeNode*> tree;
    std::vector<std::string> orderVec;
    std::string json_content;
    std::string line;
    while (std::getline(jsonFile, line)) {
        json_content = line;
        //break;
        makeJson(json_content, tree, orderVec);
    }
    // don't need this json file anymore, as the content is read into json_content.
    jsonFile.close();

  
    assignParent(tree, orderVec);
    std::unordered_map<std::string, TreeNode*>::iterator test;
    
    for(test = tree.begin(); test != tree.end(); test++) {
        tempFile << test->second->getComm() << std::endl;
    }


    std::string fullLine;
    std::string lineDos;
    std::string command;
    std::string parent_id;
    std::string id;
    std::string user;
    std::string comment;
    //std::string comments = json_content.substr(json_content.rfind("comment")+11, (json_content.find("}")) - (json_content.rfind("comment")+12));
    std::string comments = json_content.substr(json_content.rfind("comment")+11, (json_content.find("}")) - (json_content.rfind("comment")+12));
    std::cout << comments << std::endl;
    // //just make a tree object first and put them in it I suppose ??? 
    while(std::getline(inputFile, lineDos)) {
        fullLine = lineDos;
        makeInput(fullLine, tree, outputFile);
    }
    // std::cout << command << std::endl;
    // std::cout << "p: " << parent_id << std::endl;
    // std::cout << "ID: " << id << std::endl;
    // std::cout << user << std::endl;

    return 0;
    
}