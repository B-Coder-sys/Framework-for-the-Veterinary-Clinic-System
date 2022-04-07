#pragma once

void clearInputBuffer(void);
void suspend();
int inputInt();
int inputIntPositive();
int inputIntRange(int min, int max);
char inputCharOption(const char* cString);
void inputCString(char* cString, int min, int max);
void displayFormattedPhone(const char* cString);