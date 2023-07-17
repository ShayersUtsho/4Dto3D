#include <iostream>
#include <Windows.h>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

int nScreenWidth = 240;
int nScreenHeight = 80;

float fUnitOfDistance = 0.1f;

int scale = 1;
bool bFixedMap = true;
bool bCorners = true;

float fPlayerX = 8.0f * (float)scale;
float fPlayerY = 8.0f * (float)scale;
float fPlayerZ = 8.0f * (float)scale;
float fPlayerA = -3.14159f / 2.0f;
float fPlayerB = 0.0f;

int nMapLength = 16 * scale;
int nMapHeight = 16 * scale;
int nMapWidth = 16 * scale;
int nSR = (nMapLength + nMapHeight + nMapWidth) / 3 / 4;
int nSC = (nMapLength + nMapHeight + nMapWidth) / 3 / 4;

float fFOV = 3.14159f / 3.0f;
float fDepth = 16.0f * (float)scale;
float fMovementSpeed = 5.0f * (float)scale;
float fRotationSpeed = 0.8f;

int main() {
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	wstring map = L"";

	//Map Design
	if (!bFixedMap) {
		for (int fx = 0; fx < nMapLength; fx++) {
			for (int fy = 0; fy < nMapHeight; fy++) {
				for (int fz = 0; fz < nMapWidth; fz++) {
					if (((fx == 0 || fx == nMapLength - 1) ) || ((fy == 0 || fy == nMapHeight - 1) ) || ((fz == 0 || fz == nMapWidth - 1) ))
						map += L"#";
					else if ((fx - nSC) * (fx - nSC) + (fy - nSC) * (fy - nSC) + (fz - nSC) * (fz - nSC) >= nSC * nSC && (fx - nSC) * (fx - nSC) + (fy - nSC) * (fy - nSC) + (fz - nSC) * (fz - nSC) <= nSC * nSC * 2)
						map += L"#";
					else
						map += L".";
				}
			}
		}
	}

	if (bFixedMap) {
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";

		map += L"#.#.#.#..#.#.#.#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#.#.#.#..#.#.#.#";

		map += L"################";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"################";

		map += L"#.#.#.#..#.#.#.#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#.#.#.#..#.#.#.#";

		map += L"################";
		map += L"#..............#";
		map += L"#.#.#.#..#.#.#.#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"################";

		map += L"#.#.#.#..#.#.#.#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#.#.#.#..#.#.#.#";

		map += L"################";
		map += L"#..............#";
		map += L"#.#.#.#..#.#.#.#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"################";

		map += L"#.#.#.#..#.#.#.#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#.#.#.#..#.#.#.#";

		map += L"#.#.#.#..#.#.#.#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#.#.#.#..#.#.#.#";

		map += L"################";
		map += L"#..............#";
		map += L"#.#.#.#..#.#.#.#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"################";

		map += L"#.#.#.#..#.#.#.#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#.#.#.#..#.#.#.#";

		map += L"################";
		map += L"#..............#";
		map += L"#.#.#.#..#.#.#.#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"################";

		map += L"#.#.#.#..#.#.#.#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#.#.#.#..#.#.#.#";

		map += L"################";
		map += L"#..............#";
		map += L"#.#.#.#..#.#.#.#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"################";

		map += L"#.#.#.#..#.#.#.#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#..............#";
		map += L"................";
		map += L"#.#.#.#..#.#.#.#";

		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
		map += L"#.#.#.#..#.#.#.#";
		map += L"################";
	}

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	while(true){

		auto tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		if (GetAsyncKeyState((unsigned short)'W') & 0x80000) {
			fPlayerX += cosf(fPlayerA) * fMovementSpeed * fElapsedTime;
			fPlayerZ += sinf(fPlayerA) * fMovementSpeed * fElapsedTime;
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x80000) {
			fPlayerX -= cosf(fPlayerA) * fMovementSpeed * fElapsedTime;
			fPlayerZ -= sinf(fPlayerA) * fMovementSpeed * fElapsedTime;
		}
		if (GetAsyncKeyState(0x20))
			fPlayerY -= fMovementSpeed * fElapsedTime;
		if (GetAsyncKeyState(0xA0))
			fPlayerY += fMovementSpeed * fElapsedTime;

		if (GetAsyncKeyState((unsigned short)'Q') & 0x80000) {
			fPlayerX -= cosf(fPlayerA + (3.14159f / 2.0f)) * fMovementSpeed * fElapsedTime;
			fPlayerZ -= sinf(fPlayerA + (3.14159f / 2.0f)) * fMovementSpeed * fElapsedTime;
		}
		if (GetAsyncKeyState((unsigned short)'E') & 0x80000) {
			fPlayerX += cosf(fPlayerA + (3.14159f / 2.0f)) * fMovementSpeed * fElapsedTime;
			fPlayerZ += sinf(fPlayerA + (3.14159f / 2.0f)) * fMovementSpeed * fElapsedTime;
		}


		if (GetAsyncKeyState(0x25) || (GetAsyncKeyState((unsigned short)'A') & 0x80000))
			fPlayerA -= fRotationSpeed * fElapsedTime;
		if (GetAsyncKeyState(0x27) || (GetAsyncKeyState((unsigned short)'D') & 0x80000))
			fPlayerA += fRotationSpeed * fElapsedTime;
		if (GetAsyncKeyState(0x26))
			fPlayerB -= fRotationSpeed * fElapsedTime;
		if (GetAsyncKeyState(0x28))
			fPlayerB += fRotationSpeed * fElapsedTime;


		for (int y = 0; y < nScreenHeight; y++) {
			float fRayAngleB = (fPlayerB - fFOV / 2.0f) + ((float)y / (float)nScreenHeight) * fFOV;

			for (int x = 0; x < nScreenWidth; x++) {
				float fRayAngleA = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

				float fDistanceToWall = 0;
				bool bHitWall = false;
				bool bBoundary = false;

				float fEyeX = cosf(fRayAngleA) * cosf(fRayAngleB);
				float fEyeY = sinf(fRayAngleB);
				float fEyeZ = sinf(fRayAngleA) * cosf(fRayAngleB);
				
				while (!bHitWall && fDistanceToWall < fDepth) {

					fDistanceToWall += fUnitOfDistance;

					int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
					int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);
					int nTestZ = (int)(fPlayerZ + fEyeZ * fDistanceToWall);

					if (nTestX < 0 || nTestX >= nMapLength || nTestY < 0 || nTestY >= nMapHeight || nTestZ < 0 || nTestZ >= nMapWidth) {
						bHitWall = true;
						fDistanceToWall = fDepth;
					}
					else {
						if (map[nTestY * nMapLength * nMapWidth + nTestZ * nMapLength + nTestX] == '#') {
							bHitWall = true;
							if (bCorners) {
								vector<pair<float, float>> p;

								for (int tx = 0; tx < 2; tx++) {
									for (int ty = 0; ty < 2; ty++) {
										for (float tz = 0.0f; tz <= 1.0f; tz += 1.0f) {
											float vx = (float)nTestX + tx - fPlayerX;
											float vy = (float)nTestY + ty - fPlayerY;
											float vz = (float)nTestZ + tz - fPlayerZ;

											float d = sqrt(vx * vx + vy * vy + vz * vz);
											float dot = (fEyeX * vx / d) + (fEyeY * vy / d) + (fEyeZ * vz / d);
											p.push_back(make_pair(d, dot));
										}
									}
								}

								sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) {return left.first < right.first; });

								float fBound = 0.01;
								for (int ti = 0; ti < 4; ti++) {
									if (acos(p.at(ti).second) < fBound) {
										bBoundary = true;
										break;
									}
								}
							}
						}
					}



					short nShade = ' ';

					//if (fDistanceToWall <= fDepth / 8.0f)		nShade = 0x2588;
					//else if (fDistanceToWall < fDepth / 7.0f)	nShade = 0x2593;
					//else if (fDistanceToWall < fDepth / 6.0f)	nShade = 0x2592;
					//else if (fDistanceToWall < fDepth / 5.0f)	nShade = 0x2591;

					if (fDistanceToWall <=	   fDepth / 5.0f)	nShade = 0x2588;
					else if (fDistanceToWall < fDepth / 4.5f)	nShade = 0x2593;
					else if (fDistanceToWall < fDepth / 4.0f)	nShade = '@';
					else if (fDistanceToWall < fDepth / 3.5f)	nShade = '&';
					else if (fDistanceToWall < fDepth / 3.0f)	nShade = '$';
					else if (fDistanceToWall < fDepth / 2.5f)	nShade = '?';
					else if (fDistanceToWall < fDepth / 2.0f)	nShade = '+';
					else if (fDistanceToWall < fDepth / 1.5f)	nShade = '/';
					else if (fDistanceToWall < fDepth / 1.0f)	nShade = ',';
					else										nShade = ' ';

					if (bBoundary)								nShade = ',';

					screen[y * nScreenWidth + x] = nShade;


				}
			}

		}

		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
	return 0;
}