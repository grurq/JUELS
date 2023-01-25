#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "test.h"




// グローバル変数
//（生成）
int score;
int waitdef;
int myblocks[3][2];//0:落下中のもの　1:次の宝石
int drblocks[9][18][3] = {};
int graph_jl[8];
int BGM;
int hiscore;
/*
0:メインの画面　普段使い
1:抹消時の画面　0の消える宝石を白色で塗ったもの
2:　次　の画面　1で7を代入したものを抹消して下方向に詰めた物
0と1を交互に参照して2を最後に0に代入（0だけでも良いかも）
*/




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	SetWindowUserCloseEnableFlag(FALSE);
	DxLib_Init();   // DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);

	// int decwait = 50;
	SetMainWindowText("juels by grurqApps (c)2021-");
	int key = 0;

	do {


		score = 0;
		ZeroMemory(myblocks, sizeof(myblocks));
		ZeroMemory(drblocks, sizeof(drblocks));
		waitdef = defspeed;


		BGM = LoadSoundMem("music\\BGM.mp3");
		opening();
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
		pause(1);
		/*
		メインループ

		*/

		do {
			int x = 4, y = 2;
			int attach = 0;
			juels_new();

			do {
				int wait = waitdef;
				int pusedkey = 0;
				while (wait > 0) {


					key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

					//SetDrawScreen(DX_SCREEN_BACK);
					if ((key & PAD_INPUT_RIGHT) && drblocks[x + 1][y][0] == 0) x = right(x, y);
					if ((key & PAD_INPUT_LEFT) && drblocks[x - 1][y][0] == 0) x = left(x, y);


					//上下キーの押されていることを記録
					if (key & PAD_INPUT_A && !(key & PAD_INPUT_B)) pusedkey = PAD_INPUT_A;
					if (!(key &PAD_INPUT_A) && key & PAD_INPUT_B)pusedkey = PAD_INPUT_B;
					// 離した瞬間で宝石を移動

					if (!(key & PAD_INPUT_A) && pusedkey == PAD_INPUT_B && wait % 10 == 0)
					{
						sort_d(x, y); pusedkey = 0;
					}
					if (!(key & PAD_INPUT_B) && pusedkey == PAD_INPUT_A && wait % 10 == 0)
					{
						sort_u(x, y); pusedkey = 0;
					}

					if (key & PAD_INPUT_START)pause(0);
					if (key == PAD_INPUT_DOWN) { wait = 0; }
					else
					{
						wait -= decwait;
					}
					if (GetWindowUserCloseFlag(TRUE)) {
						DxLib_End();
						return 0;
					}


					WaitTimer(decwait);

					//ScreenFlip();
					//SetDrawScreen(DX_SCREEN_FRONT);

					ProcessMessage();
				}
				if (drblocks[x][y + 1][0] > 0) break;
				down(x, y);



				y++;
			} while (y < 17);
			//接地判定
			attached(x, y);
			int clearloop = 0;
			int decsc_wt = 0;
			while (maps_kill() > 0) {
				for (int h = 0; h < 4; h++) {
					PlayMusic("music\\se_DROP.wav", DX_PLAYTYPE_BACK);
					maps_draw(1);
					WaitTimer(decwait / 5);
					maps_draw(0);
					WaitTimer(decwait / 5);
				}
				WaitTimer(decwait / 5);

				decsc_wt = maps_fall();
				maps_appear();

				score += decsc_wt * 10;
				decsc_wt *= (clearloop + 1) * 5;



				maps_draw(0);

				clearloop++;
			}
			waitdef = waitdef - (200 - ((decsc_wt / 3) * 50));
			if (waitdef > defspeed)waitdef = defspeed;
			if (waitdef < 100) waitdef = 100;
			docs_sc(1);
			SetDrawScreen(DX_SCREEN_FRONT);

		} while (drblocks[4][2][0] == 0);

		SetDrawScreen(DX_SCREEN_FRONT);
		DrawFormatString(80, 220, siro, "GAME OVER");
		StopSoundMem(BGM);
		PlayMusic("music\\jingle_GAMEOVER.wav", DX_PLAYTYPE_NORMAL);
		WaitTimer(2500);

		WaitKey();
		ranking();
		
	} while (true);

		DxLib_End();
		return 0;
}