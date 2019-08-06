#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Box {
public:
	int x;
	int y;
	bool checked;
	bool flag;
	virtual char getImage()  = 0;
	virtual bool isChecked() = 0;
	virtual bool isMine() const = 0;
	virtual bool isFlagged()  = 0;
};

class Tile : virtual public Box {
public:
	char image;
	int counter;

	Tile() {
		x = 0;
		y = 0;
		flag = false;
		counter = 0;
		image = '-';
		checked = false;
	}
	virtual bool isChecked() {
		return checked;
	}
	void SetImage(char c) {
		this->image = c;
	}
	char getImage()  override {
		if (isFlagged()) {
			return 'F';
		}
		else return image;
	}
	bool isMine() const override {
		return false;
	}

	void increaseCounter() {
		counter++;
	}
	bool isFlagged()  override {
		return flag;
	}
};

///Definition of Tile methods



///Class Mine
class Mine : virtual public Box {
public:
	Mine() {
		x = 0;
		y = 0;
		flag = false;
		checked = false;
		image = 'X'; 
	}

	char image;

	virtual bool isChecked() {
		return checked;
	}
	char getImage()  override {
		if (isFlagged()) {
			return 'F';
		}
		else return image;
	}
	bool isMine() const override {
		return true;
	}
	bool isFlagged()  override {
		return flag;
	}
};