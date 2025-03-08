#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <filesystem>
#include <atomic>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace fs = std::filesystem;

std::atomic<double> speed{1.0};
const std::vector<std::string> videos = {
    "bad_apple.wav"
};

void play_audio(const std::string& video) {
    std::wstring wpath(video.begin(), video.end());
    PlaySoundW(
        wpath.c_str(), 
        NULL, 
        SND_FILENAME | SND_ASYNC
    );
}

void display_output() {
    std::string dir = "frames-ascii";
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    std::sort(files.begin(), files.end());

    for (const auto& filename : files) {
        std::ifstream file(fs::path(dir) / filename);
        if (!file) {
            std::cerr << "Error opening: " << filename << '\n';
            continue;
        }

        std::cout << file.rdbuf() << std::flush;

        int delay_ms = static_cast<int>(24 / speed.load());
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

void set_console_size(int cols, int rows) {
    std::string cmd = "mode con cols=" 
                    + std::to_string(cols) 
                    + " lines=" 
                    + std::to_string(rows);
    std::system(cmd.c_str());
}

int main(int argc, char* argv[]) {
	set_console_size(97, 37); // 设置窗口大小97列37行
	SetConsoleTitle("Bad Apple动画 by 骑士斯诺70");
    if (argc > 1) {
        speed.store(std::stod(argv[1]));
    }

    std::thread display_thread(display_output);

    std::vector<std::thread> audio_threads;
    for (const auto& video : videos) {
        audio_threads.emplace_back(play_audio, video);
    }

    for (auto& t : audio_threads) {
        t.join();
    }

    display_thread.join();

    return 0;
}