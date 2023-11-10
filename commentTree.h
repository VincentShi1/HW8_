#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <string.h>
#ifndef CommentTree_h
#define CommentTree_h

class TreeNode {
    public:
        TreeNode() : parent(NULL), left(NULL), right(NULL) {}

        //TreeNode(const std::string& init) : comment(init), parent(NULL), left(NULL), right(NULL) {};
        TreeNode(const std::string& vid_id, const std::string& auth, const std::string& cid,
                int likes, int replies, bool is_reply, const std::string& pid ,const std::string& pub_date, const std::string& crawl_date,
                bool is_owner, const std::string& comm) : 
                video_id(vid_id),author(auth), comment_id(cid), like_count(likes), reply_count(replies), is_reply(is_reply),
                parent_comment_id(pid), published_date(pub_date), crawled_date(crawl_date), is_video_owner(is_owner),
                comment(comm), parent(NULL), left(NULL), right(NULL) {};

        TreeNode(const std::string& pID, const std::string& cID, const std::string& auth, const std::string& comment) :
                published_date("0 seconds ago"), parent_comment_id(pID),comment_id(cID), author(auth), comment(comment), parent(NULL), left(NULL), right(NULL){};

        TreeNode(const std::string& cID, const std::string& auth, const std::string& comment) :
                published_date("0 seconds ago"), comment_id(cID), author(auth), comment(comment), parent(NULL), left(NULL), right(NULL){};


        // TreeNode(std::string vid_id,std::string auth, std::string cid,
        //         int likes, int replies, bool is_reply, std::string pid ,std::string pub_date, std::string crawl_date,
        //         bool is_owner,std::string comm) : 
        //         video_id(vid_id),author(auth), comment_id(cid), like_count(likes), reply_count(replies), is_reply(is_reply),
        //         parent_comment_id(pid), published_date(pub_date), crawled_date(crawl_date), is_video_owner(is_owner),
        //         comment(comm), parent(NULL), left(NULL), right(NULL) {};

        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        std::vector<TreeNode*> children;

        std::string getComm() const{return comment;}
        std::string getVID() const {return video_id;}
        std::string getAuth() const {return author;}
        std::string getCID() const {return comment_id;}
        int getLike() const {return like_count;}
        int getReplyCount() const {return reply_count;}
        bool isReply() const {return is_reply;}
        std::string getPID() const{return parent_comment_id;}
        std::string getPDate() const {return published_date;}
        std::string getCDate() const {return crawled_date;}
        bool isOwner() const {return is_video_owner;}

        void setCID(std::string c) {comment_id = c;}
        void addLike() {like_count++;}
        void setPID(std::string p) {parent_comment_id = p;}
        void addReplyCount() {reply_count++;}
        void subtractReplyCount() {reply_count--;}
        TreeNode* operator=(const TreeNode* other);
    private:
        std::string video_id;
        std::string author;
        std::string comment_id;
        int like_count;
        int reply_count;
        bool is_reply;
        std::string parent_comment_id;
        std::string published_date;
        std::string crawled_date;
        bool is_video_owner;
        std::string comment;

};

class CommentTree {
    public:
        CommentTree() : root(NULL) {}

        ~CommentTree() { destroy_tree(root); }
        void add_comment(const std::string& comment_text, const std::string& parent_id);
        void delete_comment(const std::string& comment_id);
        void display_comment(const std::string& comment_id, std::ofstream& output_file);
        void like_comment(const std::string& comment_id);
        void insert_comment(TreeNode* newNode);


    private:
        TreeNode* root;
        void destroy_tree(TreeNode* node);
        TreeNode* find_comment(const std::string comment_id, TreeNode* node);
        void in_order_traversal(TreeNode* node, std::ofstream& output_file);
};

#endif