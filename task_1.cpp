#include <iostream>
#include <deque>
 
static const int MAXIMUM_USER_ID = 1e+5 + 1;
static const size_t MAXIMUM_PAGE_NUMBER = 1000;
 
class StimulatePeople {
public:
    
    StimulatePeople() : users_count_(MAXIMUM_PAGE_NUMBER, 0),
                        pages_to_user_id_(MAXIMUM_USER_ID, 0) {}
    
    void Read(int user_id, size_t pages);    
    double Cheer(int user_id);
    
private:
    std::deque<int> users_count_;
    std::deque<size_t> pages_to_user_id_;
    
    int people_ = 0;
};
 
void StimulatePeople::Read(int user_id, 
                           size_t pages) {
 
    size_t pages_before = 0;
 
    if (pages_to_user_id_[user_id]) {
        pages_before = pages_to_user_id_[user_id];
        
    } else {
        ++people_;
    }
 
    pages_to_user_id_[user_id] = pages;
 
    for (int i = pages_before; i < pages; ++i) {
        users_count_[i] += 1;
        
    }
}
 
double StimulatePeople::Cheer(int user_id) {
 
    if (!pages_to_user_id_[user_id]) {
        return 0.0;
 
    } else if (!(people_ - 1)) {
        return 1.0;
 
    } else {
        size_t pages_to_user = pages_to_user_id_[user_id];
        if (people_ == users_count_[pages_to_user - 1]) {
            return 0.0;
            
        } else {
            return (people_ - users_count_[pages_to_user - 1]) / (people_ * 1.0 - 1.0); 
            
        }           
    }
}
 
void Request_handler(std::istream& input, 
                     std::ostream& output, 
                     StimulatePeople& stimulation) {
    
    std::string str;
    getline(input, str);
    
    int requests_amount = std::stoi(str);
 
    for (int i = 0; i < requests_amount; ++i) {
        
        std::string request_type;
        getline(input, request_type, ' ');
        
        if (request_type == "READ") {
            
            std::string user_id;
            getline(input, user_id, ' ');
            
            std::string pages;
            getline(input, pages);
            
            stimulation.Read(std::stoi(user_id), 
                             std::stoi(pages));
        } else {
            
            std::string user_id;
            getline(input, user_id);
            
            output << stimulation.Cheer(std::stoi(user_id)) << std::endl;
        }
    }
}
 
int main() {
    StimulatePeople stimulation;
    Request_handler(std::cin, 
                    std::cout, 
                    stimulation);
}