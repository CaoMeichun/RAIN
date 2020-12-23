#include<stdio.h>
#include<stdlib.h>
#include <time.h>


int Round = 30;
//unsigned char PlainKeySpace[4] = {0x0,0x5,0xa,0xf};
//unsigned char PlainKeySpace[2] = {0x2,0x3};
//unsigned char PlainKeySpace[2] = {0x1,0x9};
unsigned char PlainKeySpace[16] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
//unsigned char PlainKeySpace[16] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

unsigned char Plaintext_64[16], Tweak_64[16], Key[16];
unsigned char Tweakey_64[30][16];

//unsigned char Plaintext_64[16] = {0x5,0xf,0xa,0x0,0x5,0x0,0xa,0xa ,0xa,0x0,0x5,0x5,0x5,0xf,0x5,0xf};
//unsigned char Tweak_64[16] = {0x5,0x0,0xf,0x0,0xa,0x5,0x5,0xf,0xf,0x5,0x5,0xa,0x0,0xf,0xa,0xa};
//unsigned char Key0[16] = {0xf,0xa,0xf,0x0,0xf,0x0,0xa,0x5,0x0,0xa,0x5,0x0,0xa,0xf,0xf,0xa};
//unsigned char Key1[16] = {0xf,0xa,0x5,0x0,0xf,0xf,0xf,0xa,0xf,0xf,0xa,0x5,0x5,0x0,0x5,0xf};

void PlainKeySelect_64()
{
	srand((unsigned)time(0));
	int x;
	printf("RAIN-64:\n");
	printf("PlainText:\n");
	for (int i = 0; i < 16; i++)
	{
		x = rand() % 16;
		Plaintext_64[i] = PlainKeySpace[x];
		printf("%0x", Plaintext_64[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n\n");
	printf("Key:\n");
	for (int i = 0; i < 16; i++)
	{
		x = rand() % 16;
		Key[i] = PlainKeySpace[x];
		printf("%0x", Key[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n");
	printf("Tweak:\n");
	for (int i = 0; i < 16; i++)
	{
		x = rand() % 16;
		Tweak_64[i] = PlainKeySpace[x];
		printf("%0x", Tweak_64[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n\n");
}

void prinState_64(unsigned char* state, char* name, int round)
{
	if(round < 10)
		printf("ENC - Round0%d - %-12s: %c = ", round, name, 'S');
	else
	    printf("ENC - Round%d - %-12s: %c = ", round, name,'S');
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", state[i]);
		if (i % 4 == 3)
			printf(" ");
	}

	printf(" - %s%d = ", "Tweakey_", round);
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", Tweakey_64[round][i]);
		if (i % 4 == 3)
			printf(" ");
	}

	printf("\n");
}
void prinStateinv_64(unsigned char* state, char* name, int round)
{
	if (round < 10)
		printf("DEC - Round0%d - %-18s: %c = ", round, name, 'S');
	else
		printf("DEC - Round%d - %-18s: %c = ", round, name, 'S');
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", state[i]);
		if (i % 4 == 3)
			printf(" ");
	}

	printf(" - %s%d = ", "Tweakey_", round);
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", Tweakey_64[round][i]);
		if (i % 4 == 3)
			printf(" ");
	}

	printf("\n");
}

void prinRTK_64(unsigned char* state, char* name, int round)
{
	if (round < 10)
		printf("RTK - Round0%d - %-18s = ", round, name);
	else
		printf("RTK - Round%d - %-18s = ", round, name);
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", state[i]);
		if (i % 4 == 3)
			printf(" ");
	}

	printf("\n");
}

void MC_64(unsigned char* state_out, unsigned char* state)
{
	unsigned char state_result[16];

	unsigned char tmp;

	tmp = state[0] ^ state[4] ^ state[8] ^ state[12];
	state_result[0] = tmp ^ state[0];
	state_result[4] = tmp ^ state[8];
	state_result[8] = tmp ^ state[4];
	state_result[12] = tmp ^ state[12];

	tmp = state[1] ^ state[5] ^ state[9] ^ state[13];
	state_result[1] = tmp ^ state[1];
	state_result[5] = tmp ^ state[9];
	state_result[9] = tmp ^ state[5];
	state_result[13] = tmp ^ state[13];

	tmp = state[2] ^ state[6] ^ state[10] ^ state[14];
	state_result[2] = tmp ^ state[2];
	state_result[6] = tmp ^ state[10];
	state_result[10] = tmp ^ state[6];
	state_result[14] = tmp ^ state[14];

	tmp = state[3] ^ state[7] ^ state[11] ^ state[15];
	state_result[3] = tmp ^ state[3];
	state_result[7] = tmp ^ state[11];
	state_result[11] = tmp ^ state[7];
	state_result[15] = tmp ^ state[15];

	for (int i = 0; i < 16; i++)
	{
		state_out[i] = state_result[i];
	}

}

void SC_64(unsigned char* state_out, unsigned char* state)
{

	unsigned char Sbox[16] = { 0x0, 0x9, 0x3, 0x2, 0x6, 0x5, 0x4, 0xb, 0xc, 0x1, 0xa, 0xd, 0x8, 0xe, 0x7, 0xf };

	unsigned char state_result[16];

	int state_dec;
	for (int i = 0; i < 16; i++)
	{
		state_dec = state[i];
		state_result[i] = Sbox[state_dec];

	}
	for (int i = 0; i < 16; i++)
	{
		state_out[i] = state_result[i];
	}
}

void SCinv_64(unsigned char* state_out, unsigned char* state)
{

	unsigned char Sbox_inv[16] = { 0x0, 0x9, 0x3, 0x2, 0x6, 0x5, 0x4, 0xe, 0xc, 0x1, 0xa, 0x7, 0x8, 0xb, 0xd, 0xf };

	unsigned char state_result[16];

	int state_dec;
	for (int i = 0; i < 16; i++)
	{
		state_dec = state[i];
		state_result[i] = Sbox_inv[state_dec];

	}
	for (int i = 0; i < 16; i++)
	{
		state_out[i] = state_result[i];
	}
}

void SR_64(unsigned char* state_out, unsigned char* state)
{
	unsigned char state_result[16];
	state_result[0] = state[0];		state_result[1] = state[1];
	state_result[4] = state[5];		state_result[5] = state[6];
	state_result[8] = state[10];	state_result[9] = state[11];
	state_result[12] = state[15];	state_result[13] = state[12];

	state_result[2] = state[2];		state_result[3] = state[3];
	state_result[6] = state[7];		state_result[7] = state[4];
	state_result[10] = state[8];	state_result[11] = state[9];
	state_result[14] = state[13];	state_result[15] = state[14];

	for (int i = 0; i < 16; i++)
	{
		state_out[i] = state_result[i];
	}
}

void SRinv_64(unsigned char* state_out, unsigned char* state)
{
	unsigned char state_result[16];
	state_result[0] = state[0];		state_result[1] = state[1];
	state_result[4] = state[7];		state_result[5] = state[4];
	state_result[8] = state[10];	state_result[9] = state[11];
	state_result[12] = state[13];	state_result[13] = state[14];

	state_result[2] = state[2];		state_result[3] = state[3];
	state_result[6] = state[5];		state_result[7] = state[6];
	state_result[10] = state[8];	state_result[11] = state[9];
	state_result[14] = state[15];	state_result[15] = state[12];

	for (int i = 0; i < 16; i++)
	{
		state_out[i] = state_result[i];
	}
}

void ATK_64(unsigned char* ATK_out, unsigned char* RTK, unsigned char* state)
{
	for (int i = 0; i < 16; i++)
	{
		ATK_out[i] = state[i] ^ RTK[i];
	}
}

void AK_64(unsigned char* AK_out, unsigned char* T, unsigned char* K0)
{
	unsigned char AK[16];
	AK[0] = T[0] ^ K0[0];		AK[1] = T[1] ^ K0[1];
	AK[4] = T[4] ^ K0[4];		AK[5] = T[5] ^ K0[5];
	AK[8] = T[8] ^ K0[8];		AK[9] = T[9] ^ K0[9];
	AK[12] = T[12] ^ K0[12];		AK[13] = T[13] ^ K0[13];

	AK[2] = T[2] ^ K0[2];		AK[3] = T[3] ^ K0[3];
	AK[6] = T[6] ^ K0[6];		AK[7] = T[7] ^ K0[7];
	AK[10] = T[10] ^ K0[10];		AK[11] = T[11] ^ K0[11];
	AK[14] = T[14] ^ K0[14];		AK[15] = T[15] ^ K0[15];

	for (int i = 0; i < 16; i++)
	{
		AK_out[i] = AK[i];
	}

}

void AC_64(unsigned char* state_out, unsigned char* state, int r)
{
	unsigned int  rc[30] = { 0x7274, 0x258a, 0x45c5, 0x0f80, 0x7dd0, 0x2add, 0xc474, 0x0faf, 0xd0cd, 0x8afa,
		0xc2dc, 0x85ca, 0xf7d0, 0xc52c, 0xaacf, 0xc5cf, 0xf0c5, 0x47cd, 0x7a42, 0x0c05,
		0xdd80, 0x5dc8, 0x5754, 0xca72, 0x8c4c, 0x5802, 0x5d7a, 0x450f, 0x244f, 0xc047 };

	unsigned char state_result[16];
	for (int ii = 0; ii < 16; ii++)
	{
		state_result[ii] = state[ii];
	}

	state_result[12] = (rc[r] & 0xF) ^ state[12];
	state_result[8] = ((rc[r] >> 4) & 0xF) ^ state[8];
	state_result[4] = ((rc[r] >> 8) & 0xF) ^ state[4];
	state_result[0] = ((rc[r] >> 12) & 0xF) ^ state[0];

	for (int i = 0; i < 16; i++)
	{
		state_out[i] = state_result[i];
	}

}

void AB_64(unsigned char* state_out, unsigned char* state)
{
	unsigned char state_result[16];
	unsigned char tmp = 0;
	unsigned char tmp_bit = 0x0;
	for (int i = 0; i < 16; i++)
		state_result[i] = state[i];
	for (int i = 0; i < 16; i++)
		tmp_bit ^= state[i];

	if (tmp_bit >= 0x8)
	{
		for (int ii = 0; ii < 16; ii++)
			state_out[ii] = (state_result[ii] & 0x7) ^ 0x8;
	}
	else if (tmp_bit < 0x8)
	{
		for (int ii = 0; ii < 16; ii++)
			state_out[ii] = (state_result[ii] & 0x7) ^ 0x0;
	}
}

void KeySchdule_64(unsigned char* T, unsigned char* K0)
{

	printf("Round Tweakey RTK schdule:\n\n");
	unsigned char AK_out[16], TSR_out[16], AC_out[16];

	AK_64(AK_out, Tweak_64, K0); prinRTK_64(AK_out, "AK_out", 0);
	SR_64(TSR_out, AK_out); prinRTK_64(TSR_out, "TSR_out", 0);
	AC_64(AC_out, TSR_out, 0); prinRTK_64(AC_out, "AC_out", 0);
	AB_64(Tweakey_64[0], AC_out); prinRTK_64(Tweakey_64[0], "RTK", 0);

	for (int i = 1; i < Round; i++)
	{
		AK_64(AK_out, Tweakey_64[i - 1], K0); prinRTK_64(AK_out, "AK_out", i);
		SR_64(TSR_out, AK_out); prinRTK_64(TSR_out, "TSR_out", i);
		AC_64(AC_out, TSR_out, i); prinRTK_64(AC_out, "AC_out", i);
		AB_64(Tweakey_64[i], AC_out); prinRTK_64(Tweakey_64[i], "RTK", i);
	}

	/*for (int i = 0; i < Round; i++)
	{
		printf("Tweakey%d: \n", i);
		for (int ii = 0; ii < 16; ii++)
		{
			printf("%0x", Tweakey_64[i][ii]);
			if (ii % 4 == 3)
				printf(" ");
		}
		printf("\n");
	}*/
	printf("\n\n\n");
}

void enc_64(unsigned char* C, unsigned char* P, unsigned char* T, unsigned char* K0)
{
	unsigned char MC_out[16], SC_out[16], SR_out[16];

	for (int i = 0; i < 16; i++)
		C[i] = P[i] ^ K0[i];
	//prinState_64(C, "White", 0);


	for (int i = 0; i < Round; i++)
	{
		//        printf("Round%d: ***************************\n",i);
		MC_64(MC_out, C); prinState_64(MC_out, "MC_output",i);
		SC_64(SC_out, MC_out); prinState_64(SC_out, "SC_output",i);
		SR_64(SR_out, SC_out); prinState_64(SR_out, "SR_output",i);
		ATK_64(C, Tweakey_64[i], SR_out); prinState_64(C, "ATK_output", i);

	}

	printf("CipherText: " );
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", C[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n");

	//    for(int i = 0;i < 16;i++)
	//        C[i] = P[i];

}

void dec_64(unsigned char* P, unsigned char* C, unsigned char* T, unsigned char* K0)
{
	unsigned char MCinv_out[16], SCinv_out[16], SRinv_out[16], ATKinv_out[16];

	for (int i = 0; i < 16; i++)
		MCinv_out[i] = C[i];

	for (int i = Round - 1; i >= 0; i--)
	{
		//        printf("Round%d: ***************************\n",i);
		ATK_64(ATKinv_out, Tweakey_64[i], MCinv_out); prinStateinv_64(ATKinv_out, "ATK_inv_output",i);
		SRinv_64(SRinv_out, ATKinv_out); prinStateinv_64(SRinv_out, "SR_inv_outputput",i);
		SCinv_64(SCinv_out, SRinv_out); prinStateinv_64(SCinv_out, "SC_inv_output",i);
		MC_64(MCinv_out, SCinv_out); prinStateinv_64(MCinv_out, "MC_inv_output", i);
	}

	for (int i = 0; i < 16; i++)
		P[i] = MCinv_out[i] ^ K0[i];

	printf("CipherText_Decryption: ");
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", P[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n");

	if (memcmp(P, Plaintext_64, 16) != 0) {
		printf("解密失败 () test failed.\n");
		getchar();
	}
	printf("\n   解密  成功 \n");
}

void Test()
{
	PlainKeySelect_64();
	KeySchdule_64(Tweak_64, Key);

	unsigned char C[16], P[16];

	printf("\nEncryption:\n");
	enc_64(C, Plaintext_64, Tweak_64, Key);

	printf("\nDecryption:\n");
	dec_64(P, C, Tweak_64, Key);

	printf("End.\n");
}

int main()
{
	printf("The cipher status is written into \"RAIN-64_output.txt\" in this directory.\n");

	FILE* stream1;
	freopen_s(&stream1, "RAIN-64_output.txt", "w", stdout);

	Test();

	fclose(stdout);//关闭文件
	
    getchar();
	return 0;
}
