#pragma once
class Delivery {
public:
	std::string name;              // �������� �����. names DONE
	std::string sender;            // ����������� contries  DONE
	std::string reciever;          // ����������  contries  DONE
	std::string content;           // ����������  contents  DONE
	double weight;                 // ���
	double price;                  // ���� �����������
	double deliver_price;          // ���� ��������

	std::string destination;       // ����� ���������� companies DONE 
	std::string departure_point;   // ����� �������    companies DONE
	//Time dest_time;
	//Time depart_time;
	std::string type_of_transport; // ��� ����������. transport_types DONE
};