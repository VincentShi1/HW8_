#include <iostream>
#include "commentTree.h"
#include <utility>
#include <string.h>


TreeNode* TreeNode::operator=(const TreeNode* other) {
    if(!other) {
        return nullptr;
    }
    
    for(TreeNode* child: children) {
        delete child;
    }
    children.clear();

    comment = other->getComm();
    video_id = other->getVID();
    author = other->getAuth();
    comment_id = other->getCID();
    like_count = other->getLike();
    reply_count = other->getReplyCount();
    is_reply = other->isReply();
    parent_comment_id = other->getPID();
    published_date = other->getPDate();
    crawled_date = other->getCDate();

    for(TreeNode* child: other->children) {
        children.push_back(child);
    }

    return this;
}


void CommentTree::insert_comment(TreeNode* newNode){
    if((*newNode).getPID() == "") {
        if(!root) {
            root = newNode;
        }
        else{ 
            insert_comment(root->left);
        }
    }
    else {
        TreeNode* childNode = find_comment((*newNode).getCID(), newNode);
        if(!childNode) {
            return; //doesnt exist idk bruh
        }
        childNode->children.push_back(newNode);
    }
}

void CommentTree::add_comment(const std::string& comment_text, const std::string& parent_id) {

}

void CommentTree::display_comment(const std::string& comment_id, std::ofstream& output_file) {

}

TreeNode* CommentTree::find_comment(const std::string comment_id, TreeNode* node) {
    if(root->getCID() == comment_id) {
        return root;
    }
    else {
        for(TreeNode* child : root->children) {
            if(child->getCID() == comment_id) {
                return child;
            }
        }
    }
    return nullptr;
}