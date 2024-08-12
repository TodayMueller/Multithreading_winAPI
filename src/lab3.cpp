#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;

/*
1 - a        3
2 - bcf      9
3 - gedcf    15
4 - gerhf    15
5 - gerimn   18
6 - gkmn     12
7 - gpn      9
*/

unsigned int lab3_thread_graph_id()
{
    return 20;
}

const char* lab3_unsynchronized_threads()
{
    return "bcf";
}

const char* lab3_sequential_threads()
{
    return "gkmn";
}


const int numThreads = 14;
HANDLE hThreads[numThreads];
DWORD ThreadId;

HANDLE hMutex;
HANDLE hSemI, hSemB, hSemC, hSemE, hSemG, hSemF, hSemK, hSemM, hSemN, hSemP, hSemEnd;

// Функции для каждого потока
DWORD WINAPI ThreadA(LPVOID); // 0
DWORD WINAPI ThreadB(LPVOID); // 1
DWORD WINAPI ThreadC(LPVOID); // 2
DWORD WINAPI ThreadD(LPVOID); // 3
DWORD WINAPI ThreadE(LPVOID); // 4
DWORD WINAPI ThreadF(LPVOID); // 5
DWORD WINAPI ThreadG(LPVOID); // 6
DWORD WINAPI ThreadH(LPVOID); // 7
DWORD WINAPI ThreadI(LPVOID); // 8
DWORD WINAPI ThreadK(LPVOID); // 9
DWORD WINAPI ThreadM(LPVOID); // 10
DWORD WINAPI ThreadN(LPVOID); // 11
DWORD WINAPI ThreadP(LPVOID); // 12
DWORD WINAPI ThreadR(LPVOID); // 13


void console_log(char c) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << c << flush;
        ReleaseMutex(hMutex);
        computation();
    }
}

DWORD WINAPI ThreadA(LPVOID lpParam) {
    //1
    console_log('a');

    hThreads[1] = CreateThread(NULL, 0, ThreadB, NULL, 0, &ThreadId);
    hThreads[2] = CreateThread(NULL, 0, ThreadC, hThreads[1], 0, &ThreadId);
    hThreads[5] = CreateThread(NULL, 0, ThreadF, hThreads[2], 0, &ThreadId);

    return 0;
}

DWORD WINAPI ThreadB(LPVOID lpParam) {
    //2
    console_log('b');

    WaitForSingleObject(hSemB, INFINITE);
    return 0;
}

DWORD WINAPI ThreadC(LPVOID lpParam) {
    //2
    console_log('c');


    // Ожидание завершения потока B
    HANDLE hThreadB = (HANDLE)lpParam;
    WaitForSingleObject(hThreadB, INFINITE);
    CloseHandle(hThreads[1]);

    ReleaseSemaphore(hSemF, 1, NULL);

    // Запуск потоков D, E, F
    hThreads[3] = CreateThread(NULL, 0, ThreadD, NULL, 0, &ThreadId);
    hThreads[4] = CreateThread(NULL, 0, ThreadE, hThreads[3], 0, &ThreadId);
    hThreads[6] = CreateThread(NULL, 0, ThreadG, hThreads[4], 0, &ThreadId);

    //3
    console_log('c');

    return 0;
}

DWORD WINAPI ThreadD(LPVOID lpParam) {
    //3
    console_log('d');

    return 0;
}

DWORD WINAPI ThreadE(LPVOID lpParam) {
    console_log('e');

    HANDLE hThreadD = (HANDLE)lpParam;
    WaitForSingleObject(hThreadD, INFINITE);
    CloseHandle(hThreads[3]);

    WaitForSingleObject(hSemE, INFINITE);
    ReleaseSemaphore(hSemG, 1, NULL);
    ReleaseSemaphore(hSemF, 1, NULL);

    console_log('e');

    WaitForSingleObject(hSemE, INFINITE);
    ReleaseSemaphore(hSemG, 1, NULL);
    //5
    console_log('e');

    ReleaseSemaphore(hSemG, 1, NULL);

    return 0;
}

DWORD WINAPI ThreadF(LPVOID lpParam) {
    //2
    console_log('f');

    ReleaseSemaphore(hSemB, 1, NULL);
    WaitForSingleObject(hSemF, INFINITE);

    //3
    console_log('f');

    // Ожидание завершения потока C
    HANDLE hThreadC = (HANDLE)lpParam;
    WaitForSingleObject(hThreadC, INFINITE);
    CloseHandle(hThreads[2]);

    ReleaseSemaphore(hSemE, 1, NULL);
    WaitForSingleObject(hSemF, INFINITE);

    // Запуск потоков R, H
    hThreads[7] = CreateThread(NULL, 0, ThreadH, hThreads[5], 0, &ThreadId);
    hThreads[13] = CreateThread(NULL, 0, ThreadR, hThreads[7], 0, &ThreadId);

    //4
    console_log('f');

    return 0;
}

DWORD WINAPI ThreadG(LPVOID lpParam) {

    for (int i = 0; i < 3; i++) {
        console_log('g');
        WaitForSingleObject(hSemG, INFINITE);
    }

    HANDLE hThreadE = (HANDLE)lpParam;
    WaitForSingleObject(hThreadE, INFINITE);
    CloseHandle(hThreads[4]);
    
    //6
    ReleaseSemaphore(hSemM, 1, NULL);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemG, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << 'g' << flush;
        ReleaseMutex(hMutex);
        computation();
        ReleaseSemaphore(hSemM, 1, NULL);
    }

    //7
    ReleaseSemaphore(hSemN, 1, NULL);
    console_log('g');

    ReleaseSemaphore(hSemN, 1, NULL);
    return 0;
}

DWORD WINAPI ThreadH(LPVOID lpParam) {
    //4
    console_log('h');

    // Ожидание завершения потока F
    HANDLE hThreadF = (HANDLE)lpParam;
    WaitForSingleObject(hThreadF, INFINITE);
    CloseHandle(hThreads[5]);

    return 0;
}

DWORD WINAPI ThreadI(LPVOID lpParam) {
    //5
    console_log('i');

    HANDLE hThreadR = (HANDLE)lpParam;
    WaitForSingleObject(hThreadR, INFINITE);
    CloseHandle(hThreads[13]);

    WaitForSingleObject(hSemI, INFINITE);

    return 0;
}

DWORD WINAPI ThreadK(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemK, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << 'k' << flush;
        ReleaseMutex(hMutex);
        computation();
        ReleaseSemaphore(hSemN, 1, NULL);
    }

    return 0;
}

DWORD WINAPI ThreadM(LPVOID lpParam) {
    //5
    console_log('m');

    HANDLE hThreadI = (HANDLE)lpParam;
    WaitForSingleObject(hThreadI, INFINITE);
    CloseHandle(hThreads[8]);

    hThreads[9] = CreateThread(NULL, 0, ThreadK, NULL, 0, &ThreadId);
    //6

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemM, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << 'm' << flush;
        ReleaseMutex(hMutex);
        computation();
        ReleaseSemaphore(hSemK, 1, NULL);
    }

    return 0;

}

DWORD WINAPI ThreadN(LPVOID lpParam) {
    //5 
    console_log('n');

    ReleaseSemaphore(hSemI, 1, NULL);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemN, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << 'n' << flush;
        ReleaseMutex(hMutex);
        computation();
        ReleaseSemaphore(hSemG, 1, NULL);
    }

    HANDLE hThreadM = (HANDLE)lpParam;
    WaitForSingleObject(hThreadM, INFINITE);
    CloseHandle(hThreads[10]);

    hThreads[12] = CreateThread(NULL, 0, ThreadP, hThreads[11], 0, &ThreadId);

    WaitForSingleObject(hSemN, INFINITE);
    console_log('n');

    WaitForSingleObject(hSemN, INFINITE);

    return 0;
}

DWORD WINAPI ThreadP(LPVOID lpParam) {
    //1
    console_log('p');

    HANDLE hThreadN = (HANDLE)lpParam;
    WaitForSingleObject(hThreadN, INFINITE);
    CloseHandle(hThreads[11]);

    ReleaseSemaphore(hSemEnd, 1, NULL);

    return 0;
}

DWORD WINAPI ThreadR(LPVOID lpParam) {
    //4
    console_log('r');

    // Ожидание завершения потока H
    HANDLE hThreadH = (HANDLE)lpParam;
    WaitForSingleObject(hThreadH, INFINITE);
    CloseHandle(hThreads[7]);

    hThreads[8] = CreateThread(NULL, 0, ThreadI, hThreads[13], 0, &ThreadId);
    hThreads[10] = CreateThread(NULL, 0, ThreadM, hThreads[8], 0, &ThreadId);
    hThreads[11] = CreateThread(NULL, 0, ThreadN, hThreads[10], 0, &ThreadId);


    ReleaseSemaphore(hSemE, 1, NULL);

    //5
    console_log('r');

    return 0;
}

int lab3_init() {
    // Создание мьютекса
    hMutex = CreateMutex(NULL, FALSE, NULL);
    if (!hMutex) {
        cout << "Error creating mutex." << endl;
        return 1;
    }

    // Создание семафоров
    hSemB = CreateSemaphore(NULL, 0, 1, NULL);
    hSemC = CreateSemaphore(NULL, 0, 1, NULL);
    hSemE = CreateSemaphore(NULL, 0, 1, NULL);
    hSemF = CreateSemaphore(NULL, 0, 1, NULL);
    hSemG = CreateSemaphore(NULL, 0, 1, NULL);
    hSemK = CreateSemaphore(NULL, 0, 1, NULL);
    hSemM = CreateSemaphore(NULL, 0, 1, NULL);
    hSemN = CreateSemaphore(NULL, 0, 1, NULL);
    hSemP = CreateSemaphore(NULL, 0, 1, NULL);
    hSemI = CreateSemaphore(NULL, 0, 1, NULL);

    hSemEnd = CreateSemaphore(NULL, 0, 1, NULL);

    if (!hSemC || !hSemE || !hSemG || !hSemF || !hSemK || !hSemM || !hSemN || !hSemP) {
        cout << "Error creating semaphores." << endl;
        return 1;
    }

    // Запускаем поток A
    hThreads[0] = CreateThread(NULL, 0, ThreadA, NULL, 0, &ThreadId);

    // Ожидание завершения всех потоков
    WaitForSingleObject(hSemEnd, INFINITE);

    CloseHandle(hThreads[6]);
    CloseHandle(hThreads[9]);
    CloseHandle(hThreads[12]);

    // Закрываем дескриптор мьютекса
    CloseHandle(hMutex);

    // Закрываем дескрипторы семафоров после завершения всех потоков
    CloseHandle(hSemB);
    CloseHandle(hSemC);
    CloseHandle(hSemE);
    CloseHandle(hSemF);
    CloseHandle(hSemG);
    CloseHandle(hSemK);
    CloseHandle(hSemM);
    CloseHandle(hSemN);
    CloseHandle(hSemP);
    CloseHandle(hSemI);

    return 0;
}
