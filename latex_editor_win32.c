// #include <windows.h>
// #include <commdlg.h>
// #include <stdio.h>
// #include <stdlib.h>

// #define ID_FILE_OPEN 1
// #define ID_FILE_SAVE 2
// #define ID_LATEX_CONVERT 3
// #define ID_EXIT 4

// HWND hEdit;  // Handle for the text editor
// HWND hStatus;  // Handle for the status bar

// // Function to display errors from LaTeX processing
// void DisplayError(HWND hwnd, const char *message) {
//     MessageBox(hwnd, message, "Error", MB_OK | MB_ICONERROR);
// }

// // Function to convert LaTeX to PDF and handle errors
// void ConvertLatex(HWND hwnd) {
//     char latex_code[65536];
//     GetWindowText(hEdit, latex_code, sizeof(latex_code));
    
//     FILE *file = fopen("temp.tex", "w");
//     if (file == NULL) {
//         DisplayError(hwnd, "Error creating LaTeX file.");
//         return;
//     }
    
//     // Write LaTeX code to a temp file
//     fprintf(file, "%s", latex_code);
//     fclose(file);

//     // Run pdflatex
//     int result = system("pdflatex -output-directory=. temp.tex > latex_output.log 2>&1");
//     if (result != 0) {
//         DisplayError(hwnd, "Error compiling LaTeX. Check latex_output.log.");
//     } else {
//         MessageBox(hwnd, "LaTeX compilation successful. Check the generated PDF.", "Success", MB_OK | MB_ICONINFORMATION);
//     }
// }

// // Function to open a .tex file
// void OpenLaTeXFile(HWND hwnd) {
//     OPENFILENAME ofn;
//     char szFile[260] = {0};
//     char fileContent[65536] = {0};
    
//     ZeroMemory(&ofn, sizeof(ofn));
//     ofn.lStructSize = sizeof(ofn);
//     ofn.hwndOwner = hwnd;
//     ofn.lpstrFile = szFile;
//     ofn.nMaxFile = sizeof(szFile);
//     ofn.lpstrFilter = "TeX Files\0*.tex\0All Files\0*.*\0";
//     ofn.nFilterIndex = 1;
//     ofn.lpstrFileTitle = NULL;
//     ofn.nMaxFileTitle = 0;
//     ofn.lpstrInitialDir = NULL;
//     ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
//     if (GetOpenFileName(&ofn)) {
//         FILE *file = fopen(ofn.lpstrFile, "r");
//         if (file) {
//             fread(fileContent, sizeof(char), sizeof(fileContent), file);
//             SetWindowText(hEdit, fileContent);
//             fclose(file);
//         } else {
//             DisplayError(hwnd, "Error opening file.");
//         }
//     }
// }

// // Function to save LaTeX code to a .tex file
// void SaveLaTeXFile(HWND hwnd) {
//     OPENFILENAME ofn;
//     char szFile[260] = {0};
//     char latex_code[65536] = {0};
    
//     GetWindowText(hEdit, latex_code, sizeof(latex_code));

//     ZeroMemory(&ofn, sizeof(ofn));
//     ofn.lStructSize = sizeof(ofn);
//     ofn.hwndOwner = hwnd;
//     ofn.lpstrFile = szFile;
//     ofn.nMaxFile = sizeof(szFile);
//     ofn.lpstrFilter = "TeX Files\0*.tex\0All Files\0*.*\0";
//     ofn.nFilterIndex = 1;
//     ofn.lpstrFileTitle = NULL;
//     ofn.nMaxFileTitle = 0;
//     ofn.lpstrInitialDir = NULL;
//     ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
//     if (GetSaveFileName(&ofn)) {
//         FILE *file = fopen(ofn.lpstrFile, "w");
//         if (file) {
//             fprintf(file, "%s", latex_code);
//             fclose(file);
//         } else {
//             DisplayError(hwnd, "Error saving file.");
//         }
//     }
// }

// // Function to create menus
// void AddMenus(HWND hwnd) {
//     HMENU hMenu = CreateMenu();
//     HMENU hFileMenu = CreateMenu();
    
//     AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, "Open");
//     AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE, "Save");
//     AppendMenu(hFileMenu, MF_STRING, ID_LATEX_CONVERT, "Convert LaTeX");
//     AppendMenu(hFileMenu, MF_STRING, ID_EXIT, "Exit");
    
//     AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
//     SetMenu(hwnd, hMenu);
// }

// // Window procedure function
// LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
//     switch (msg) {
//         case WM_COMMAND:
//             switch (wp) {
//                 case ID_FILE_OPEN:
//                     OpenLaTeXFile(hwnd);
//                     break;
//                 case ID_FILE_SAVE:
//                     SaveLaTeXFile(hwnd);
//                     break;
//                 case ID_LATEX_CONVERT:
//                     ConvertLatex(hwnd);
//                     break;
//                 case ID_EXIT:
//                     PostQuitMessage(0);
//                     break;
//             }
//             break;
//         case WM_CREATE:
//             hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE,
//                                    10, 10, 760, 400, hwnd, NULL, NULL, NULL);
//             hStatus = CreateWindowEx(0, "STATIC", "Status: Ready", WS_CHILD | WS_VISIBLE,
//                                      10, 420, 760, 20, hwnd, NULL, NULL, NULL);
//             AddMenus(hwnd);
//             break;
//         case WM_DESTROY:
//             PostQuitMessage(0);
//             break;
//         default:
//             return DefWindowProc(hwnd, msg, wp, lp);
//     }
//     return 0;
// }

// // Entry point
// int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
//     WNDCLASS wc = {0};
//     wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
//     wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//     wc.hInstance = hInst;
//     wc.lpszClassName = "latexWindowClass";
//     wc.lpfnWndProc = WindowProcedure;

//     if (!RegisterClass(&wc)) return -1;

//     HWND hwnd = CreateWindow("latexWindowClass", "LaTeX Editor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 500,
//                              NULL, NULL, NULL, NULL);
    
//     MSG msg = {0};
//     while (GetMessage(&msg, NULL, 0, 0)) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }
    
//     return 0;
// }
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_FILE_OPEN 1
#define ID_FILE_SAVE 2
#define ID_LATEX_CONVERT 3
#define ID_EXIT 4

HWND hEdit;  // Handle for the text editor
HWND hStatus;  // Handle for the status bar

// Function to display error messages
void DisplayError(HWND hwnd, const char *message) {
    MessageBox(hwnd, message, "Error", MB_OK | MB_ICONERROR);
}

// Function to convert LaTeX to PDF and handle errors
void ConvertLatex(HWND hwnd) {
    char latex_code[65536];
    GetWindowText(hEdit, latex_code, sizeof(latex_code));
    
    FILE *file = fopen("temp.tex", "w");
    if (file == NULL) {
        DisplayError(hwnd, "Error creating LaTeX file.");
        return;
    }
    
    // Write LaTeX code to a temp file
    fprintf(file, "%s", latex_code);
    fclose(file);

    // Run pdflatex to convert the LaTeX file to PDF
    int result = system("pdflatex -output-directory=. temp.tex > latex_output.log 2>&1");
    if (result != 0) {
        DisplayError(hwnd, "Error compiling LaTeX. Check latex_output.log.");
    } else {
        MessageBox(hwnd, "LaTeX compilation successful. Check the generated PDF.", "Success", MB_OK | MB_ICONINFORMATION);
    }
}

// Function to open a .tex file
void OpenLaTeXFile(HWND hwnd) {
    OPENFILENAME ofn;
    char szFile[260] = {0};
    char fileContent[65536] = {0};
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "TeX Files\0*.tex\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileName(&ofn)) {
        FILE *file = fopen(ofn.lpstrFile, "r");
        if (file) {
            fread(fileContent, sizeof(char), sizeof(fileContent), file);
            SetWindowText(hEdit, fileContent);
            fclose(file);
        } else {
            DisplayError(hwnd, "Error opening file.");
        }
    }
}

// Function to save LaTeX code to a .tex file
void SaveLaTeXFile(HWND hwnd) {
    OPENFILENAME ofn;
    char szFile[260] = {0};
    char latex_code[65536] = {0};
    
    GetWindowText(hEdit, latex_code, sizeof(latex_code));

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "TeX Files\0*.tex\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (GetSaveFileName(&ofn)) {
        FILE *file = fopen(ofn.lpstrFile, "w");
        if (file) {
            fprintf(file, "%s", latex_code);
            fclose(file);
        } else {
            DisplayError(hwnd, "Error saving file.");
        }
    }
}

// Function to create menus
void AddMenus(HWND hwnd) {
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, "Open");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE, "Save");
    AppendMenu(hFileMenu, MF_STRING, ID_LATEX_CONVERT, "Convert LaTeX");
    AppendMenu(hFileMenu, MF_STRING, ID_EXIT, "Exit");
    
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    SetMenu(hwnd, hMenu);
}

// Window procedure function
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case ID_FILE_OPEN:
                    OpenLaTeXFile(hwnd);
                    break;
                case ID_FILE_SAVE:
                    SaveLaTeXFile(hwnd);
                    break;
                case ID_LATEX_CONVERT:
                    ConvertLatex(hwnd);
                    break;
                case ID_EXIT:
                    PostQuitMessage(0);
                    break;
            }
            break;
        case WM_CREATE:
            hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE,
                                   10, 10, 760, 400, hwnd, NULL, NULL, NULL);
            hStatus = CreateWindowEx(0, "STATIC", "Status: Ready", WS_CHILD | WS_VISIBLE,
                                     10, 420, 760, 20, hwnd, NULL, NULL, NULL);
            AddMenus(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

// Entry point
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASS wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "latexWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) return -1;

    HWND hwnd = CreateWindow("latexWindowClass", "LaTeX Editor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 500,
                             NULL, NULL, NULL, NULL);
    
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
