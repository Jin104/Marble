#include "graphics.h"
#include "draw.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "player.h"
#include "local.h"

void StartGame() {
	system("mode con: cols=130 lines=48");
	while (1) {
		DrawMap();
	}
}

void Loading() {


}

void Explain() {


}