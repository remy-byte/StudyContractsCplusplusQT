#pragma once

#include <iostream>
#include <string>

using std::string;
using std::cout;

class Contract {

private:
	string subject;
	int duration = 0;
	string type;
	string teacher_name;
public:

	Contract() = default;

	Contract(const string subject, int duration, const string type, const string teacher_name) :subject{ subject }, duration{ duration }, type{ type }, teacher_name{ teacher_name } {}

	Contract(const Contract& other) :subject{ other.subject }, duration{ other.duration }, type{ other.type }, teacher_name{ other.teacher_name } {
		//cout << "!!!!!!!!!!!!!!!!!!!!!\n";
	}

	string get_Subject() const {
		return subject;
	}

	int get_Duration()const noexcept {
		return duration;
	}

	string get_Type() const {
		return type;
	}

	string get_Teacher_name() const {
		return teacher_name;
	}

	void set_Subject(string new_subject) {
		subject = new_subject;
	}

	void set_Duration(int new_duration) {
		duration = new_duration;
	}

	void set_Type(string new_type) {
		type = new_type;
	}

	void set_Teacher_name(string new_teacher_name) {
		teacher_name = new_teacher_name;
	}

	string to_string() const {
		return "Nume: " + this->subject + " Duratie: " + std::to_string(this->duration) + " Tip: " + this->type + " Teacher: " + this->teacher_name;
	}

};

bool compare_subject(const Contract& contract, const Contract& other);

bool compare_duration(const Contract& contract, const Contract& other);