#pragma once
class Delivery {
public:
	std::string name;              // �������� �����.
	std::string sender;            // �����������
	std::string reciever;          // ����������
	std::string content;           // ����������
	double weight;                 // ���
	double price;                  // ���� �����������
	double deliver_price;          // ���� ��������

	std::string destination;       // ����� ����������
	std::string departure_point;   // ����� �������
	//Time dest_time;
	//Time depart_time;
	std::string type_of_transport; // ��� ����������.
};