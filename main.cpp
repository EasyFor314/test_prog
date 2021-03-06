#include <windows.h>
#include <string>

HWND hwndEdit_text;
HWND hwndEdit_col;
HWND hwndShow_str;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_COMMAND:	

            if (HIWORD(wParam) == BN_CLICKED) 
			{
			
				int len = GetWindowTextLength(hwndEdit_text) + 1;
	            char* text = new char[len];
	            GetWindowText(hwndEdit_text, text, len);  
				 
				int len_col = GetWindowTextLength(hwndEdit_col) + 1;
	            char* col = new char[len_col];
				GetWindowText(hwndEdit_col, col, len_col);
				
				int col_r = atoi( col );
			
				for( int i = 0 ; i < (col_r)  ; i++ )
				{
				//MessageBox(NULL, text , col, MB_OK)	;
				HWND rr = 	CreateWindowW(L"Static", L"", 
                WS_CHILD | WS_VISIBLE,
                200, 
				20*i, 
				90, 
				25, 
				hwnd, 
				NULL, 
				NULL, 
				NULL); 
				SetWindowText( rr, text );
					
				}
								               			    
		
            }

            break;
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */




	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE); // ���
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}


	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,
		NULL,
		hInstance,
		NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}	
		
hwndEdit_text = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                50, 
				50, 
				150, 
				20, 
				hwnd, 
				NULL,
				NULL,
				NULL);
				
hwndEdit_col = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                50, 
				100, 
				150, 
				20, 
				hwnd, 
				NULL,
				NULL,
				NULL);	
							             
CreateWindowW(  L"Button", 
                L"Ok",
                WS_VISIBLE | WS_CHILD ,
                20, 
				150, 
				100, 
				25, 
				hwnd, 
				NULL,
				NULL,
				NULL);  
CreateWindowW(L"Static", L"Stroka:", 
                WS_CHILD | WS_VISIBLE,
                50, 
				20, 
				90, 
				25, 
				hwnd, 
				NULL, 
				NULL, 
				NULL); 
CreateWindowW(L"Static", L"Col-vo:", 
                WS_CHILD | WS_VISIBLE,
                50, 
				70, 
				90, 
				25, 
				hwnd, 
				NULL, 
				NULL, 
				NULL);
             
	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
