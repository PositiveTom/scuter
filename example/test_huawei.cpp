#include <iostream>
#include <vector>
#include <malloc.h>

#include <unordered_map>

//  树上逃离

class TreeNode {
public:
    int val_;
    bool obstacles_;
    std::vector<TreeNode*> child;
public:
    TreeNode(int val):val_(val),obstacles_(false){}
    
    void AddChildNode(TreeNode* node_ptr) {
        child.push_back(node_ptr);
    }

    void SetConstant() {
        obstacles_ = true;
    }
};

//  0-1-3-4  
//  0-2-5-6
std::vector<std::vector<int>> all_path;
std::vector<int> path;
void Back(TreeNode* node) {
    if(node->obstacles_)
        return;
    if(node->child.empty()) {
        path.push_back(node->val_);
        all_path.push_back(path);
        return;
    }

    for(int i=0; i<node->child.size(); i++) {
        path.push_back(node->val_);
        Back(node->child[i]);
        if(node->child[i]->obstacles_)
            path.pop_back();
        else if(!node->child[i]->obstacles_) {
            path.pop_back();
            path.pop_back();
        }
    }
}


int main() {
    int n;
    std::cin >> n;
    int edge;
    std::cin >> edge;

    TreeNode* root_ptr = new TreeNode(0);

    std::unordered_map<int, TreeNode*> node_val_node_ptr;
    node_val_node_ptr.insert(std::make_pair(0, root_ptr));

    for(int i=0; i<edge; i++) {
        std::vector<int> xy;
        int x, y;
        std::cin >> x >> y;

        if(node_val_node_ptr.find(x) != node_val_node_ptr.end()) {
            TreeNode* node_ptr = new TreeNode(y);
            TreeNode* father_ptr = node_val_node_ptr[x];
            father_ptr->AddChildNode(node_ptr);
            node_val_node_ptr.insert(std::make_pair(y, node_ptr));
        }
    }
    int block;
    std::cin >> block;
    
    for(int i=0; i<block; i++) {
        int a;
        std::cin >> a;
        node_val_node_ptr[a]->SetConstant();
    }
    // std::cout << "debug1" << std::endl;
    // std::cout << "debug: " << root_ptr->child.size() << std::endl;
    Back(root_ptr);
    
    // std::cout << "debug2" << std::endl;
    //  进一步筛选
    int min_path = 99999;
    int original_path_id = -1;
    for(int i=0; i<all_path.size(); i++) {
        if(min_path > all_path[i].size()) {
            min_path = all_path[i].size();
            original_path_id = i;
        } else if(min_path == all_path[i].size()) {
            std::vector<int> &original_path = all_path[original_path_id];
            std::vector<int> &current_path = all_path[i];
            for(int j=0; j<original_path.size(); j++) {
                if(current_path[j] < original_path[j]) {
                    original_path_id = i;
                    break;
                }
            }
        }
    }


    if(all_path.size() != 0) {
        std::vector<int> &final_path = all_path[original_path_id];
        std::cout << final_path.size() << std::endl;
        for(int i=0; i<final_path.size(); i++) {
            if(i < final_path.size()-1)
                std::cout << final_path[i] << "->";
            else
                std::cout << final_path[i];
        }
    } else {
        std::cout << "NULL" << std::endl;
    }

    return 0;
}