#ifndef WORD_H
#define WORD_H

#include <QtCore/QString>
#include <vector>

std::vector<QString> mVectorOfWords{
    "hello"
    "freedom"
    "disturb"
    "cat"
    "knowledge"
    "success"
    "hacking"
    "building"
    "cities"
    "computer"
    "linux"
    "programming language"
    "love"
    "marriage"
    "husband"
    "laptop"
    "motherboard"
    "keyboard"
    "monitor"
    "desktop"
    "kitchen"
    "electricity"
    "furniture"
};

std::vector<QString> homeRelatedWords{
    "furniture"
    "kitchen"
    "refregarator"
    "room"
    "windows"
    "blanket"
    "pillow"
    "sheet"
    "toilet"
};

std::vector<QString> computerRelatedWords{
    "motherboard"
    "monitor"
    "graphics card"
    "ALU"
    "central proccesing unit"
    "hard disk"
    "keyboard"
    "bytes"
    "information"
    "data"
    "internet"
    "power phase"
    "download"
    "thread"
    "kernel"
    "interrupt"
    "service"
    "handler"
    "virtual memory"
    "BIOS"
    "hardware"
    "hacking"
    "Linux kernel"
};

#endif		//WORD_H
