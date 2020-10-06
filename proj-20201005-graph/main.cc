// ������ ��������� ��� ������ �� 5.10.2020-6.10.2020
//
/*
	������:
	��������� ������ �������
		z = sinc(sqrt(x*x + y*y))

	��� 1. ��������� ������� ��� �������� ��������� �� ��������� �������
			(x, y, z) � ���������� ����� �� �������� (sx, sy)
			� ������ ���������� ������������� �� ���� ��� ����
	��� 2. ��������� ������ �������, ��������� ���� ���������� � ������� �����,
			� ������ - � ��������� �����.
	��� 2.5. ��������� ������ ��� ���, ������� ������� ��� �� ����.

		(�� ������ ����� � ��� ��� ��������� ����� ������, ��....)

	��� 3. ��� �������� ��������� ����� ������� ����������� ��������
			"���������� ���������"
				1. ������ ������ �������� �� ������� �������� � �������
				2. ���� ��������� ����� ��������� ���� ����� ���������,
					�� � �� ������
				3. ���� ��������� ����� ��������� ���� ����� ���������, ��:
					* ����� ������;
					* ��������� � ���� ������� ����������� �������� �� ������
					  ����� �����
				4. ����� ������ �������� ��������� ������� (� ����������������
					����������) �������� ��������.

		������� ����������: -30 <= x <= 30 � -30 <= y <= 30 (��������)
 */

#include <fstream>
#include <cmath>
#include <cstdint>
#include <vector>

// ��� � ��� ��������� ��������� TGA-�����
#pragma pack(push, 1)
struct TGA_Header
{
	uint8_t id_len;			// ����� ��������������
	uint8_t pal_type;		// ��� �������
	uint8_t img_type;		// ��� �����������
	uint8_t pal_desc[5];	// �������� �������
	uint16_t x_pos;			// ��������� �� ��� X
	uint16_t y_pos;			// ��������� �� ��� Y
	uint16_t width;			// ������
	uint16_t height;		// ������
	uint8_t depth;			// ������� �����
	uint8_t img_desc;		// ��������� �����������
};
#pragma pack(pop)

constexpr uint16_t IMG_WIDTH = 1920;
constexpr uint16_t IMG_HEIGHT = 1080;
constexpr uint32_t COL_BACKGROUND = 0xff003f3f;
constexpr uint32_t COL_FOREGROUND = 0xffcfcfcf;

// ��� ����� �� ������������ ���� ���������

double sinc(double x)
{
	if (x == 0) return 1.;
	return sin(x) / x;
}

double my_evil_function(double x, double y)
{
	return sinc(hypot(x, y));
}


int main()
{
	// ��������� ������ ������� � ��������� ������
		std::vector<uint32_t> picture(IMG_WIDTH * IMG_HEIGHT);
		for (auto && p : picture) p = COL_BACKGROUND;


		/*for(unsigned x = 0; x < IMG_WIDTH; x++){
		        for(unsigned y = 0; y < IMG_HEIGHT; y++){
		            if((x==IMG_WIDTH/2)){
		                picture[y*IMG_WIDTH+x] = COL_FOREGROUND;
		                std::cout<< "x= " << x << " y=" << y <<std::endl;}
		        }
		    }

		*/
	// ����� ��� �� ������������ ��� ���.



	// �������� ����������� ����������� � ���� ������� TGA
	TGA_Header hdr {};
	hdr.width = IMG_WIDTH;
	hdr.height = IMG_HEIGHT;
	hdr.depth = 32;
	hdr.img_type = 2;
	hdr.img_desc = 0x28;

	// ������ ����� + ��������� ����� ����
	std::ofstream tga_file { "output.tga", std::ios::binary };
	// ���������� ��������� � ������ ��������
	tga_file.write(reinterpret_cast<char*>(&hdr), sizeof(hdr));
	tga_file.write(reinterpret_cast<char*>(&picture[0]),
	picture.size() * sizeof(uint32_t));
	// ��������� ����
	tga_file.close();

	return 0;
}



