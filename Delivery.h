#pragma once
class Delivery {
public:
	std::string* name;              // �������� �����. names DONE
	std::string* content;           // ����������  contents  DONE
	int weight;                    // ���
	int price;                     // ���� �����������
	int deliver_price;             // ���� ��������
	std::string* sender;            // ����������� contries  DONE
	std::string* departure_point;   // ����� �������    companies DONE
	//Time depart_time;
	std::string* reciever;          // ����������  contries  DONE
	std::string* destination;       // ����� ���������� companies DONE 
	//Time dest_time;
	std::string* type_of_transport; // ��� ����������. transport_types DONE
};