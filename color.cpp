/*
 color.cpp
 Copyright (c) 2025 Maksim Yarovoy
*/

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>

void print_help() {
    std::cout << "Usage: color [COLOR] [OPTIONS] [TEXT]\n"
              << "Example: echo 'Hello' | color red --bold --underline --bright\n\n"
              << "Colors:\n"
              << "  black, red, green, yellow, blue, magenta, cyan, white\n\n"
              << "Options:\n"
              << "  --bold          Makes the text bold\n"
              << "  --underline     Underlines the text\n"
              << "  --blink         Makes the text blink\n"
              << "  --reverse       Reverses the foreground and background colors\n"
              << "  --bright        Uses bright colors\n"
              << "  --background    Sets the background color\n"
              << "  --help          Prints this help message\n\n";
}

int parse_color(const std::string& color) {
    static const std::map<std::string, int> color_map = {
        {"black", 30}, {"red", 31}, {"green", 32}, {"yellow", 33},
        {"blue", 34}, {"magenta", 35}, {"cyan", 36}, {"white", 37},
        {"black_bright", 90}, {"red_bright", 91}, {"green_bright", 92},
        {"yellow_bright", 93}, {"blue_bright", 94}, {"magenta_bright", 95},
        {"cyan_bright", 96}, {"white_bright", 97}
    };

    auto it = color_map.find(color);
    if (it != color_map.end()) {
        return it->second;
    }

    std::cerr << "error " << color << "'.\n";
    print_help();
    exit(1);
}

std::vector<std::string> parse_arguments(int argc, char* argv[]) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    return args;
}

std::string process_input(const std::string& input, bool bold, bool underline, bool blink, bool reverse, int color_code, int bg_color_code) {
    std::ostringstream oss;
    oss << "\033[";

    if (bold)    oss << "1;";
    if (underline) oss << "4;";
    if (blink)   oss << "5;";
    if (reverse) oss << "7;";

    oss << color_code;
    if (bg_color_code >= 0) {
        oss << ";48;5;" << bg_color_code;
    }
    oss << "m" << input << "\033[0m";
    return oss.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    bool bold = false, underline = false, blink = false, reverse = false, bright = false;

    std::string color, bg_color;
    std::vector<std::string> args = parse_arguments(argc, argv);

    color = args[0];
    for (size_t i = 1; i < args.size(); ++i) {
        const auto& arg = args[i];
        if (arg == "--bold")          bold = true;
        else if (arg == "--underline") underline = true;
        else if (arg == "--blink")    blink = true;
        else if (arg == "--reverse")  reverse = true;
        else if (arg == "--bright")   bright = true;
        else if (arg == "--help") {
            print_help();
            return 0;
        } else if (arg == "--background" && i + 1 < args.size()) {
            bg_color = args[++i];
        }
    }

    int color_code = parse_color(color);
    if (bright) color_code += 60;
    int bg_color_code = bg_color.empty() ? -1 : parse_color(bg_color);
    std::string input;
    while (std::getline(std::cin, input)) {
        std::cout << process_input(input, bold, underline, blink, reverse, color_code, bg_color_code) << std::endl;
    }

    return 0;
}

