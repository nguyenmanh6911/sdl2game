#include "declare.h"
#include "ranking.h"
#include "graphic.h"
#include "Init.h"

// Lấy điểm cao nhất trong level đang chơi
int get_highest_score(int level) {
    ifstream file;
    string line;
    int highestScore = 0;

    // Mở file theo level
    if (level == 1) file.open("ranking1.txt");
    else if (level == 2) file.open("ranking2.txt");
    else if (level == 3) file.open("ranking3.txt");


    if (!file.is_open()) {
        return 0; 
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string playerName;
        int score;

        if (getline(ss, playerName, ',') && ss >> score) { //Lấy dữ liệu từ trước dấu phẩy -> playerName, sau dấu phẩy -> score
            if (score > highestScore) {
                highestScore = score; // Cập nhật highest score nếu tìm thấy điểm cao hơn
            }
        }
    }

    file.close();
    return highestScore; 
}

void saveScore(const string& playerName1, int score, int level) {
    ofstream file;
    if (level == 1) file.open("ranking1.txt", ios::app);
    else if (level == 2) file.open("ranking2.txt", ios::app);
    else if (level == 3) file.open("ranking3.txt", ios::app);

    if (file.is_open()) {
        file << playerName1 << "," << score << "\n"; // Nhập tên, điểm vào file
        file.close();
    }
}

bool compareScores(const PlayerScore& a, const PlayerScore& b) {
    return a.score > b.score;  // Trả về người có điểm cao hơn
}

void saveTop5Scores(int level) {
    vector<PlayerScore> rankings;
    
    // Đọc dữ liệu từ file
    ifstream file;
    if (level == 1) file.open("ranking1.txt");
    else if (level == 2) file.open("ranking2.txt");
    else if (level == 3) file.open("ranking3.txt");
    string line;
    
    while (getline(file, line)) {
        size_t vitridauphay = line.find(',');  // Tìm vị trí dấu phẩy
        string name = line.substr(0, vitridauphay);  // Lấy tên trước dấu phẩy
        int score = stoi(line.substr(vitridauphay + 1));  // Lấy điểm sau dẩu phẩy
        rankings.push_back({name, score});
        
    }
    file.close();

    // Sắp xếp danh sách điểm theo thứ tự giảm dần
    sort(rankings.begin(), rankings.end(), compareScores);

    // Giữ lại top 5 người có điểm cao nhất
    if (rankings.size() > 5) {
        rankings.resize(5);
    }

    // Ghi lại top 5 vào file
    ofstream outFile;
    if (level == 1) outFile.open("ranking1.txt", ios::trunc);
    else if (level == 2) outFile.open("ranking2.txt", ios::trunc);
    else if (level == 3) outFile.open("ranking3.txt", ios::trunc);
    if (outFile.is_open()) {
        for (const auto& player : rankings) {
            outFile << player.name << "," << player.score << "\n";
        }
        outFile.close();
    }
}

void show_ranking(int level) {
    vector<PlayerScore> rankings;
    ifstream file;
    if (level == 1) file.open("ranking1.txt");
    else if (level == 2) file.open("ranking2.txt");
    else if (level == 3) file.open("ranking3.txt");
    if (!file) {
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
            string name = line.substr(0, commaPos);  // Lấy tên
            int score = stoi(line.substr(commaPos + 1));  // Lấy điểm
            rankings.push_back({name, score});
    }
    file.close();

  
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Nền đen
    SDL_RenderFillRect(renderer, NULL);
    renderTexture(returnimage, returnrect);
    renderTexture (homeimage,homerect);
    

    loadtext_Realsize(renderer, "font/Lobster-Regular.ttf", 80, purple, "TOP 5 PRO PLAYERS", 150, 50);

    // Hiển thị danh sách xếp hạng
    int y = 180;
    for (int i = 0; i < min(5, (int)rankings.size()); i++) {
        string text = to_string(i + 1) + ". " + rankings[i].name + ": " + to_string(rankings[i].score);
        loadtext_Realsize(renderer, "font/arial.ttf", 50, white, text.c_str(), 350, y);
        y += 120;
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(16); // Hiển thị trong 2 giây
}



