
#pragma once

/* �f�t�H���g�E�B���h�E�T�C�Y��640*480 */


/* �F�̒萔�錾 */
#define kuro		0x000000
#define ao			0x0000ff
#define aka			0xff0000
#define murasaki	0xff00ff
#define midori		0x00ff00
#define mizuiro		0x99ffff
#define daidai		0xff9900
#define siro		0xffffff

#define juel0	"pics\\0.png"
#define juel1	"pics\\1.png"
#define juel2	"pics\\2.png"
#define juel3	"pics\\3.png"
#define juel4	"pics\\4.png"
#define juel5	"pics\\5.png"
#define juel6	"pics\\6.png"
#define juel7	"pics\\7.png"



#define defspeed	1600
#define decwait		75


// �O���[�o���ϐ���`
extern int score;
extern int hiscore;
extern int waitdef;
extern int BGM;
extern int myblocks[3][2];//0:�������̂��́@1:���̕��
extern int drblocks[9][18][3];
extern int graph_jl[8];


//�O���t�B�b�N
int putblock(int x, int y, int cr);
int opening(void);
int docs_sc(int words);
int juels_next(void);
int juels_new(void);
int juels_draw(int x, int y, int flag);
int colors(void);


//����
int kill(int x, int y);
int down(int x, int y);
int right(int x, int y);
int left(int x, int y);
int sort_u(int x, int y);
int sort_d(int x, int y);
int pause(int flag);

//�ڒn
int attached(int x, int y);


//�}�b�v����
int maps_kill(void);
int mapseek_u(int x, int y);
int mapseek_lu(int x, int y);
int mapseek_ru(int x, int y);
int mapseek_r(int x, int y);
int maps_fall(void);
int maps_appear(void);
int maps_draw(int flag);



int colors(void) {
	graph_jl[0] = LoadGraph(juel0);
	graph_jl[1] = LoadGraph(juel1);
	graph_jl[2] = LoadGraph(juel2);
	graph_jl[3] = LoadGraph(juel3);
	graph_jl[4] = LoadGraph(juel4);
	graph_jl[5] = LoadGraph(juel5);
	graph_jl[6] = LoadGraph(juel6);
	graph_jl[7] = LoadGraph(juel7);
	return  0;
}

int putblock(int x, int y, int cr) {
	switch (cr) {
	case 1:	DrawGraph(x, y, graph_jl[1], FALSE); break;
	case 2:	DrawGraph(x, y, graph_jl[2], FALSE); break;
	case 3:	DrawGraph(x, y, graph_jl[3], FALSE); break;
	case 4:	DrawGraph(x, y, graph_jl[4], FALSE); break;
	case 5:	DrawGraph(x, y, graph_jl[5], FALSE); break;
	case 6:	DrawGraph(x, y, graph_jl[6], FALSE); break;
	case 7:	DrawGraph(x, y, graph_jl[7], FALSE); break;
	default:DrawGraph(x, y, graph_jl[0], FALSE); break;
	}

	return 0;
}
int opening(void) {
	
	colors();
	ClearDrawScreen();
	//����
	CreateFontToHandle("���C���I", 11, -1, DX_FONTTYPE_ANTIALIASING);
	//�w�i
	for (int lx = 0; lx < 640; lx += 5) {
		for (int ly = 0; ly < 480; ly += 5) {

			// yoko
			DrawLine(0, ly, 640, ly, mizuiro);
			//tate
			DrawLine(lx, 0, lx, 480, mizuiro);
		}
	}
	//�����X�y�[�X
	DrawBox(0, 0, 227, 452, daidai, TRUE);
	DrawBox(0, 0, 225, 450, kuro, TRUE);

	// �X�R�A�E�B���h�E
	DrawBox(352, 60, 512, 220, daidai, TRUE);
	docs_sc(1);

	// ���̕��
	DrawBox(352, 290, 512, 452, daidai, TRUE);
	DrawBox(354, 292, 510, 450, kuro, TRUE);
	DrawString(412, 305, "next", siro);
	
	juels_next();


	SetDrawScreen(DX_SCREEN_FRONT);
	return 0;
}

int docs_sc(int words) {
	/*
	�X�R�A�y�уw���v�E�B���h�E
	0:�폜
	1:�X�R�A�i�v���C�E�|�[�Y���j
	2:�w���v�̂�
	3:�ҋ@�i�J�n�O�j
	*/
	SetDrawScreen(DX_SCREEN_BACK);

	switch (words) {
	case 1:
		DrawBox(354, 62, 510, 218, kuro, TRUE);
		DrawString(377, 135, "����:move\nZ X :swap\n��  :fall\nESC :pause", siro);
		if (score > hiscore) hiscore = score;
			DrawFormatString(367, 75, siro, "hiscore:%7d\n  score:%7d\n  speed:%7d",hiscore, score, defspeed - waitdef);	
		break;
	case 2:
		DrawBox(354, 62, 510, 218, kuro, TRUE);
		DrawString(377, 135, "����:move\nZ X :swap\n��  :fall\nESC :pause", siro);
		break;
	case 3:
		DrawBox(354, 62, 510, 218, kuro, TRUE);
		DrawString(377, 135, "����:move\nZ X :swap\n��  :fall\nESC :pause", siro);
		DrawFormatString(377, 85, siro, "juels by grurqApps\n since  2019");
		break;
	default:
		DrawBox(354, 62, 510, 218, kuro, TRUE);
		break;
	}
	ScreenFlip();
	SetDrawScreen(DX_SCREEN_FRONT);
	return 0;
}

int juels_next(void) {

	for (int i = 0; i < 3; i++) {
		myblocks[i][1] = GetRand(5) + 1;
		//printfDx("%d", myblocks[i][1]);

	}
		juels_draw(415, 400, 1);

	return 0;
}
int juels_new(void) {
	for (int i = 0; i < 3; i++) {
		myblocks[i][0] = myblocks[i][1];
		//printfDx("%d", myblocks[i][0]);
	}
	juels_next();
	juels_draw(100, 50, 0);
	return 0;
}
int juels_draw(int x, int y, int flag) {
	//SetDrawScreen(DX_SCREEN_BACK);

	int dx = x, dy = y;
	for (int i = 0; i < 3; i++) {
		putblock(dx, dy - (25 * i), myblocks[i][flag]);

	}
	//ScreenFlip();
	SetDrawScreen(DX_SCREEN_FRONT);
	return 0;
}

int pause(int flag){
	int stop = 0;
	switch (flag)
	{
	case 1:

		DrawFormatString(60, 200, siro, "JUELS\nHIT ANY KEY\nto START\n\nSOUNDS by\nPANICPUMPKIN");

		if (stop != KEY_INPUT_ESCAPE) { WaitKey(); }
		SetDrawScreen(DX_SCREEN_BACK);
		DrawBox(60, 200, 225, 320, kuro, TRUE);
		ScreenFlip();
		//SetDrawScreen(DX_SCREEN_FRONT);
		break;
	default:
		StopSoundMem(BGM);
		PlayMusic("music\\se_PAUSE.wav", DX_PLAYTYPE_BACK);
		if (stop != KEY_INPUT_ESCAPE) { WaitKey(); }
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
		PlayMusic("music\\se_PAUSE.wav", DX_PLAYTYPE_BACK);
		break;
	}

	return 0;

}
// �s���p
int kill(int x, int y){

	int dx = x, dy = y;
	for (int i = 0; i < 3; i++) {
		putblock(dx, dy - (i * 25), kuro);
	}

	return 0;
}
int down(int x,int y) {
	int dx = x * 25, dy = y * 25;
	SetDrawScreen(DX_SCREEN_BACK);
	kill(dx, dy);
	dy = (y+1) * 25;
	juels_draw(dx, dy, 0);
	ScreenFlip();
	SetDrawScreen(DX_SCREEN_FRONT);

	return 0;
}
int right(int x, int y) {
	PlayMusic("music\\se_MOVE.wav", DX_PLAYTYPE_BACK);
	int dx = x * 25, dy = y * 25;
	if (x < 8) {

		kill(dx, dy);
		dx = (x + 1) * 25;
		juels_draw(dx, dy, 0);

		return ++x;//x++���ƒl���ς��Ȃ�
	}else{
		return x;
	}

}
int left(int x, int y){
	PlayMusic("music\\se_MOVE.wav", DX_PLAYTYPE_BACK);
	int dx = x * 25, dy = y * 25;
	if (x > 0) {

		kill(dx, dy);
		dx = (x - 1) * 25;
		juels_draw(dx, dy, 0);

		return --x;//x--���ƒl���ς��Ȃ�
	}
	else {
		return x;
	}

	return 0;
}

int sort_u(int x, int y){
	/*
	2:ac
	1:ba
	0:cb
	*/

	int swblocks[3];
	swblocks[0] = myblocks[0][0];
	swblocks[1] = myblocks[1][0];
	swblocks[2] = myblocks[2][0];

	myblocks[0][0] = swblocks[2];
	myblocks[1][0] = swblocks[0];
	myblocks[2][0] = swblocks[1];
	juels_draw(x * 25, y * 25, 0);
	PlayMusic("music\\se_SORT_U.wav", DX_PLAYTYPE_BACK);
	return 0;
}
int sort_d(int x, int y){
	/*
	����
	2:ab
	1:bc
	0:ca
	*/
	int swblocks[3];
	swblocks[0] = myblocks[0][0];
	swblocks[1] = myblocks[1][0];
	swblocks[2] = myblocks[2][0];

	myblocks[0][0] = swblocks[1];
	myblocks[1][0] = swblocks[2];
	myblocks[2][0] = swblocks[0];
	juels_draw(x * 25, y * 25, 0);
	PlayMusic("music\\se_SORT_D.wav", DX_PLAYTYPE_BACK);
	return 0;
}
// �ڒn�ȍ~�̏���
int attached(int x, int y) {


	for (int i = 0; i < 3; i++) {
		drblocks[x][y-i][0]=myblocks[i][0];
		//printfDx("%d", drblocks[x][y - i][0]);
	}


	return 0;
}

// �}�b�v�E��������
int maps_kill(void) { // �����z��ϐ��̓���
	int lines = 0;
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 18; y++) {
			int judge = 0;
			int(*seek[4])(int x, int y);
			if (y > 1) {
				seek[judge] = mapseek_u; judge++; //��
				if (x >= 2) {
					seek[judge] = mapseek_lu; judge++;/* ����*/}
				}
				if (x < 16) {
					if (judge > 0) {
						seek[judge] = mapseek_ru; judge++;/*�E��*/}
						seek[judge] = mapseek_r; judge++;// �E
					}
					//�֐��|�C���^�̏��������s
					for (int d = 0; d < judge; d++) { lines+=(*seek[d])(x,y); }
				}
				
			}
			//���ȊO�̕����ŗ����W�ɃR�s�[�B
		for (int h = 0; h<9; h++) {
			for (int i = 0; i<18; i++) {
				if(drblocks[h][i][1]<7)drblocks[h][i][1] = drblocks[h][i][0];
				
				}
			}
			return lines;
		}

//�ȉ�mapseek_�͏�֐��̂��߂̌����p
int mapseek_u(int x, int y) {// ��
				int dc = drblocks[x][y][0];
				if (dc>0 && 7>dc)
				{
					int same = 0;
					for (int h = 1; h<3; h++) {
						if (dc == drblocks[x][y + h][0])same++;
					}

					if (same == 2) {
						for (int i = 0; i < 3; i++) { drblocks[x][y + i][1] = 7; 	
						}
						return 1;
					}
				}

				//for (int j = 0; j < 3; j++) { drblocks[x][y + j][1] = drblocks[x][y + j][0]; }

				return 0;
			}
int mapseek_lu(int x, int y) {// ����
				int dc = drblocks[x][y][0];
				if (dc > 0 && 7 > dc)
				{

					int same = 0;
					for (int h = 1; h < 3; h++) {
						if (dc == drblocks[x - h][y + h][0])same++;
					}

					if (same == 2) {
						for (int i = 0; i < 3; i++) { drblocks[x - i][y + i][1] = 7; }
						return 1;
					}
				}
				//for (int j = 0; j < 3; j++) { drblocks[x - j][y + j][1] = drblocks[x - j][y + j][0]; }
				return 0;
			}

int mapseek_ru(int x, int y) {// �E��
				int dc = drblocks[x][y][0];
				if (dc > 0 && 7 > dc)
				{

					int same = 0;
					for (int h = 1; h < 3; h++) {
						if (dc == drblocks[x + h][y + h][0])same++;
					}

					if (same == 2) {
						for (int i = 0; i < 3; i++) { drblocks[x + i][y + i][1] = 7; }
						return 1;

					}
				}
				//for (int j = 0; j < 3; j++) { drblocks[x + j][y + j][1] = drblocks[x + j][y + j][0]; }
				return 0;
			}

int mapseek_r(int x, int y) {// �E
				int dc = drblocks[x][y][0];
				if (dc > 0 && 7 > dc)
				{
					int same = 0;
					for (int h = 1; h < 3; h++) {
						if (dc == drblocks[x + h][y][0])same++;
					}

					if (same == 2) {
						for (int i = 0; i < 3; i++) { drblocks[x + i][y][1] = 7; }
						return 1;
					}
				}
				//for (int j = 0; j < 3; j++) { drblocks[x + j][y][1] = drblocks[x + j][y][0]; }
				return 0;
			}

int maps_fall(void) {//�c���̃`�F�b�N
	int sw;
	int killed;
	int killed_r; // ���߂̏��������̐�
	int killed_t=0; //���������̍��v
	for (int h = 0; h<9; h++) {
		killed_r = 0;
		do
		{
			killed = 0;

		for (int i = 17; i >= 0; i--) {

			if (drblocks[h][i][1] == 7 || drblocks[h][i][1] == 0) {
				if (drblocks[h][i][1] == 7)killed++;
				if (i>0) {/*��������̂��̂𗎉������闎���[�u*/ 
					sw = drblocks[h][i - 1][1];
					drblocks[h][i - 1][1] = 0;
					drblocks[h][i][1] = sw;
				}
				else {
					drblocks[h][i][1] = 0;
				}
			}
		}
		if (killed > killed_r)killed_r = killed;
		} while ( killed >0);
		killed_t += killed_r;
	}
	return killed_t;
}



int maps_appear(void) {//���
				for (int h = 0; h<9; h++) {
					for (int i = 0; i<18; i++) {
						drblocks[h][i][0] = drblocks[h][i][1];
					}
				}
				return 0;
			}

int maps_draw(int flag) {//�`�� �O�̂��ߕ\�����w��ł���悤�ɂ����B
		SetDrawScreen(DX_SCREEN_BACK);

				for (int x = 0; x<9; x++) {
					for (int y = 0; y<18; y++) {
						// ���[�h�O���t
						putblock(x * 25, y * 25, drblocks[x][y][flag]);
					}
				}

				ScreenFlip();
				//SetDrawScreen(DX_SCREEN_FRONT);

				return 0;
			}
