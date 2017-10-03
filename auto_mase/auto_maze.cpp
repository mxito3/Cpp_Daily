// auto_maze.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
using namespace std;
struct cell
{
	int cell_order;
	int rank;//���
	int parent;
};

struct a_pair_cell//��pre<later
{
	int pre;
	int later;
};
// ��pre����  
bool compare(const a_pair_cell &m1, const a_pair_cell &m2)
{
	return m1.pre < m2.pre;
}

typedef struct a_pair_cell pair_cell;
typedef struct cell ce;
int width,height,margin_left = 20, margin_bottom = 60, cell_width = 8,total_way_quantity=0;//����ȫ����������ػ�
class Set;
class Create_map
{
private:
	//friend class Set;
	static vector<pair_cell>barrier_across;//����
	static vector<pair_cell>barrier_vertical;//����
	static vector<int>cells_in_way;
	pair_cell temp;
	int cell_quantity;
	int *first_select;//��һ��ѡ�������Ǹ������
	int **head_temp;
	int **have_way;//��¼һ�����ӿ��Ե�����Щ��
	int *book;
	int *book_in_way;
	//static int *cells_in_way;
	int *cell_max_selected_times;
	int *cell_selected_times;//���ӱ�ѡ�����Ĵ���
	int *can_not_choose;
	int total_cell_quantity;
	int now_cell_quantity;
	int step;//��¼���˶��ٲ�
public:
	Create_map();
	void remove_barrier(ce &pre, ce &later,Set &set0);//��ǽ
	pair_cell choose_two_cells();
	void draw_map();
	void handle_set();
	void find_best_way(int now_position, Set &set);
	int **get_head_temp();
	bool check_whether_in_way(int n);
}; 
//int *Create_map::cells_in_way=new int[width*height + 1];
vector<int> init_cells_in_way()
{
	vector<int> a;
	return a;
}
vector<pair_cell> init_across()
{
	vector<pair_cell> a;
	/*pair_cell m;
	m.later = -1;
	m.pre = -1a.*/
	return a;
}
vector<pair_cell> init_vertical()
{
	vector<pair_cell> a;
	return a;
}
vector<int> Create_map::cells_in_way(init_cells_in_way());
vector<pair_cell>  Create_map::barrier_across(init_across());//����
vector<pair_cell>  Create_map::barrier_vertical(init_vertical());//����
int **Create_map::get_head_temp()
{
	return head_temp;
}
Create_map::Create_map()
{
	//total_way_quantity = 0;//��ǰû��·
	total_cell_quantity = (height - 2) * 6 + 4 + (height - 2)*(width - 2) * 2;
	now_cell_quantity = 0;
	cell_max_selected_times = new int[width*height + 1];
	cell_selected_times = new int[width*height + 1];
	book = new int[width*height + 1];
	head_temp = new int*[width*height+1];
	have_way = new int*[width*height + 1];
	first_select = new int[width*height+1];
	book_in_way = new int[width*height + 1];
	can_not_choose = new int[width*height + 1];//�����Щ���Ӳ�����ѡ��
	for (int i = 1; i <= width*height; i++)
	{
		book[i] = 0;
		can_not_choose[i] = 0;
		cell_selected_times[i] = 0;//��ѡ������ʼ��Ϊ0
		cell_max_selected_times[i] = 4;
		first_select[i] = 0;
		book_in_way[i] = 0;
		head_temp[i] = new int[5];
		have_way[i] = new int[5];
		if (i == 1 || i == width || i == (height - 1)*width + 1 || i == width*height)//�Ľ�
		{
			cell_max_selected_times[i] = 2;
		}
		if ((i < width && i>1) || (i > (height - 1)*width + 1 && i< height*width) || (i%width == 1 && i > width && i < (height - 1)*width) || (i%width == 0 && i != width &&i != height*width))
		{
			cell_max_selected_times[i] = 3;
		}
	}
	for (int i = 1; i <= width*height; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			head_temp[i][j] = 0;
			have_way[i][j] = 0;
		}
	}
	
}
bool Create_map::check_whether_in_way(int n)
{
	//for (int i = 0;i<)
	return 1;
}
void mydisplay()
{
	Create_map map;
	map.handle_set();
}
class Set//ͼ�ɸ��ӹ���
{
private:
	ce *set;
	int quantity;//��������
	//int *remove;//�����ǽ
	//static Set set0;
public:
	Set(int m);//m�Ǹ��ӵ�����
	ce find_set(int m);//Ѱ��m�ĸ��ڵ�
	bool check_finished();
	void union_set(int root1, int root2);//��������ͨ������һ��
	ce* get_set();
};//���鼯
Set::Set(int m)//m�Ǹ��ӵ�����
{
	quantity = m;
	set = (ce*)malloc((m + 1)*sizeof(ce));
	//remove = new int[quantity+1];//�����ǽ	
	set[0].cell_order = -10;
	set[0].parent = -10;
	set[0].rank = -10;
	for (int i = 1; i <= m; i++)
	{
		set[i].cell_order = i;
		set[i].parent = i;//��ʾ���ǵ����ĸ���
		set[i].rank = 0;//���߶���0
						//remove[i] = -1;
	}
	
}
ce Set::find_set(int m)//Ѱ��m�ĸ��ڵ�

{
	if (set[m].parent==set[m].cell_order)
	{
		return set[m];
	}
	else
	{
		//while (set[m].parent != set[m].cell_order)
		//{
			//m = set[m].parent;
		//}
		 set[m].parent = find_set(set[m].parent).parent;
		 return set[m];
	}
}
bool Set::check_finished()
{
	int i;
	for (i = 2; i <= width*height; i++)
	{
		if (find_set(1).parent != find_set(i).parent)
		{
			return false;
		}

	}
	//if (i == width*height)
	//{
	//	union_set(1, width*height);
	//}
	//cout <<endl<< "β��"<<set[width*height].parent;
	//cout << endl <<"��ͷ "<< set[1].parent;
	return true;
	
}
void Set::union_set(int root1, int root2)//��������ͨ������һ��
{
	if (root1 == root2)//i��j���Ǹ����ж������ǲ���ͬһ��cell
	{
		return;
	}
	else
	{
		set[root1].parent = set[root2].cell_order;//û��rank
	}
}
ce* Set::get_set()
{
	return set;
}
class GL_fun
{
public:
	void init();
};

void GL_fun::init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1000, 0.0, 800);
}
void Create_map::remove_barrier(ce &pre,ce &later,Set &set0)
{
	if (pre.parent == later.parent)
	{
		return;
	}
	pair_cell temp;
	if(pre.cell_order < later.cell_order)
	{
		temp.pre = pre.cell_order;
		temp.later = later.cell_order;
	}
	else
	{
		temp.pre = later.cell_order;
		temp.later = pre.cell_order;
	}


	int m = set0.find_set(temp.pre).parent;
	int n = set0.find_set(temp.later).parent;
	if (m==n )//ͬһ����ͨ��
	{
		return;
	}
	else//��ͬ��ͨ��
	{
		if (temp.later <= temp.pre)
		{
			cout << "������";
		}
		((temp.later - temp.pre) == width) ? barrier_across.push_back(temp) : barrier_vertical.push_back(temp);//ѹջ
		for (int i = 0; i < 5; i++)
		{
			if (have_way[temp.pre][i] == 0)
			{
				have_way[temp.pre][i] = temp.later;//�����������ã�ʹ��ͼ��˫��ͼ
				break;
			}
		
		}
		for (int i = 0; i < 5; i++)
		{
			if (have_way[temp.later][i] == 0)
			{
				have_way[temp.later][i] = temp.pre;
				break;
			}
			
		}
		set0.union_set(m,n);//����
	}
}
void Create_map::handle_set()
{
	Set set0(width*height);
	Create_map map0;
	pair_cell cell;
	while (1)
	{
		ce* cell_temp = set0.get_set();//ÿִ��һ�ξ͵����»�ȡһ��
		cell.pre = -1;
		cell.later = -1;
		if (set0.check_finished())
		{
			break;
		}
		else
		{
			cell=map0.choose_two_cells();
			//cout << "ѡ������" << cell.pre << "   " << cell.later << endl;
			map0.remove_barrier(cell_temp[cell.pre], cell_temp[cell.later],set0);
		}
	}
	//cout << "��Ӧ��" << endl;
	map0.find_best_way(1,set0);
//	map0.cells_in_way[1] = 1;
	map0.draw_map();
	for (int i = 1; i <= width*height; i++)
	{
		if (map0.have_way[i][4] != 0)
		{
			cout << map0.have_way[i][4] << "�������������������һ������";
		}
		/*cout << endl<<i<<":";
		for (int j = 0; j < 5; j++)
		{
			cout << [j] << "   ";
		}*/
	}
	
	/*for (int i = 1; i <= width*height; i++)
	{
		cout << endl << i << ":";
		for (int j = 0; j < 4; j++)
		{
			cout << map0.have_way[i][j] << "     ";
		}

	}*/
}
void Create_map::draw_map()
{
    //handle_set();
	//cout << "������";
	int draw_across_times=width*(height-1);//�ֱ������Ҫ�Ĵ���
	int draw_vertical_times=height*(width-1);
	int all_across_border=height+1;//�߿�
	int all_vertical_border=width+1;
	int temp=0;
	int temp1 = 0;
	vector<pair_cell>::iterator it;
	sort(barrier_across.begin(), barrier_across.end(), compare);//��������
	sort(barrier_vertical.begin(), barrier_vertical.end(), compare);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	//������
	for (int i = 0; i < all_across_border;i++)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2i(margin_left, margin_bottom+i*cell_width);
		glVertex2i(margin_left + width*cell_width, margin_bottom + i*cell_width);
		glEnd();
	}
	for (int j = 0; j < all_vertical_border; j++)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2i(margin_left+j*cell_width, margin_bottom);
		glVertex2i(margin_left+j*cell_width, margin_bottom + height*cell_width);
		glEnd();
	}
	
	//������ǵ���
	glColor3f(0.0, 0.0, 0.0);
	//��������
	for (it = barrier_across.begin(); it != barrier_across.end(); it++)
	{
		temp1 = 1;
		temp = (it->pre) % width;
		if (temp == 0)
		{
			temp = width;
			temp1 = 0;
		}
		if (temp == 0)
		{
			temp = width;
		}//tempָ����ÿһ�д����������ĵڼ���
		
		glBegin(GL_LINE_STRIP);
		glVertex2i(margin_left + cell_width*(temp -1), margin_bottom + ((it->pre) / width + temp1)*cell_width);
		glVertex2i(margin_left + cell_width*(temp), margin_bottom + ((it->pre) / width +temp1)*cell_width);
		glEnd();
	}
	//��������
	for (it = barrier_vertical.begin(); it != barrier_vertical.end(); it++)
	{
		temp = (it->pre) % width;
		if (temp == 0)
		{
			temp = width;
		}
		glBegin(GL_LINE_STRIP);
		glVertex2i(margin_left + (temp)*cell_width, margin_bottom + ((it->pre) / width)*cell_width);
		glVertex2i(margin_left + (temp)*cell_width, margin_bottom + ((it->pre) / width+1)*cell_width);
		glEnd();
	}
	//������ʼ�����ֹ��
	glBegin(GL_LINE_STRIP);
	glVertex2i(margin_left, margin_bottom);
	glVertex2i(margin_left + cell_width, margin_bottom);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(margin_left + (width - 1)*cell_width, margin_bottom + height*cell_width);
	glVertex2i(margin_left + (width)*cell_width, margin_bottom + height*cell_width);
	glEnd();
	//��·��
	glColor3f(0.0, 0.0, 1.0);
	int i = 0, selected_cell1 = 1, selected_cell2 = 1;
	int j = 0;
	int first_time = 1;
	int circle_times = cells_in_way.size();
	int exchange = 0;
	if (circle_times == 0)
	{
		cout << "Խ����";
		exit(0);
	}
	for (int k = 0; k < circle_times-1; k++)
	{
		if (abs(cells_in_way[k] - cells_in_way[k + 1]) != 1 && abs(cells_in_way[k] - cells_in_way[k + 1]) != width)
		{
			cout <<cells_in_way[k]<<"������!"<<"    ";
				//exit(0);
		}
	}
	
	while (i <circle_times)
	{
		//while(cells_in_way[i] == 0)
		if (exchange == 1)
		{
			selected_cell2 = selected_cell1;
			exchange = 0;
		}
		if (first_time)
		{
			selected_cell1 = cells_in_way[i];
			first_time = 0;
			i++;
		}
		else
		{
			selected_cell1 = selected_cell2;
		}

		    selected_cell2 = cells_in_way[i];
			if (selected_cell2 == 0)
			{
				while (selected_cell2 == 0 && i <= circle_times)
				{
					i++;
					if (i > circle_times)
					{
						temp = 22;
						break;
					}
					selected_cell2 = cells_in_way[i];
				}
				if (temp == 22)
				{
					break;
				}
			}
			i++;
			//cout << "ѡ��������:"<<selected_cell1 << "     " << selected_cell2 << endl;
			if (selected_cell2 < selected_cell1)
			{
				int t = selected_cell2;
				selected_cell2 = selected_cell1;
				selected_cell1 = t;
				exchange = 1;
			}

			temp = selected_cell1%width;
			temp1 = selected_cell1 / width;
			if (selected_cell1%width == 0)
			{
				temp1--;
			}
			if (temp == 0)
			{
				temp = width;
			}
			if (selected_cell2 - selected_cell1 == width)//����
			{
				glBegin(GL_LINE_STRIP);
				glVertex2i(margin_left+(temp-1)*cell_width+cell_width/2,margin_bottom+(temp1)*cell_width+cell_width/2);
				glVertex2i(margin_left+(temp - 1)*cell_width + cell_width / 2, margin_bottom + (temp1+1)*cell_width + cell_width / 2);
				glEnd();
			}
			if (selected_cell2 - selected_cell1 == 1)//����
			{
				glBegin(GL_LINE_STRIP);
				glVertex2i(margin_left+(temp - 1)*cell_width + cell_width / 2, margin_bottom + (selected_cell1 / width)*cell_width+cell_width / 2);
				glVertex2i(margin_left+(temp)*cell_width + cell_width / 2, margin_bottom + (selected_cell1 / width)*cell_width + cell_width / 2);
				glEnd();
			}

		
	}
	cout << "������";
	//cout << "�������ˣ�";
	
	glFlush();
}
void Create_map::find_best_way(int now_position,Set &set)
{
	//cout << now_position<<endl;
	//���·���еĸ���
	if (total_way_quantity >= 1)
	{
		return;
	}
	int size1 = cells_in_way.size();
	int have_checked = 0;
	if (size1 >= 2)
	{
	
		while (abs(cells_in_way[cells_in_way.size() - 1] - now_position) != width &&abs(cells_in_way[cells_in_way.size() - 1] - now_position) != 1)
		{
			cells_in_way.pop_back();
			if (cells_in_way.size() <= 0)
			{
				break;
			}
		}
		/*while (cells_in_way[cells_in_way.size() - 1] == cells_in_way[cells_in_way.size() - 3] || cells_in_way[cells_in_way.size() - 1] == cells_in_way[cells_in_way.size() - 2])
		{
			cells_in_way.pop_back();

		}
		have_checked = 1;
		int t = cells_in_way[size - 2];//�����ڶ���
			if (abs(cells_in_way[size - 1] - cells_in_way[size - 2]) != width && abs(cells_in_way[size - 1] - cells_in_way[size - 2]) != 1)
			{
				cells_in_way.pop_back();
				cells_in_way.pop_back();
				cells_in_way.push_back(t);
			}
			have_checked = 0;
	*/
	}
	size1 = cells_in_way.size();
	if (size1 > 5)
	{
		if ((abs(cells_in_way[size1 - 1] - cells_in_way[size1 - 4]) == 1 && abs(cells_in_way[size1 - 2] - cells_in_way[size1 - 3]) == 1)||(abs(cells_in_way[size1 - 1] - cells_in_way[size1 - 4]) == width && abs(cells_in_way[size1 - 2] - cells_in_way[size1 - 3]) == width))
		{
			for (int i = 0; i < 5; i++)
			{
				if (have_way[cells_in_way[cells_in_way.size() - 4]][i] == cells_in_way[cells_in_way.size() - 1] && have_way[cells_in_way[cells_in_way.size() - 4]][i] != 0)
				{
					cout << endl << "�ҵ����Ǹ����������" << cells_in_way[size1 - 4];
					int t = cells_in_way[cells_in_way.size() - 1];
					cells_in_way.pop_back();
					cells_in_way.pop_back();
					cells_in_way.pop_back();
					cells_in_way.push_back(t);
				}
			}
		}
	}

	cells_in_way.push_back(now_position);
	//cells_in_way[now_position] = now_position;
	//book_in_way[now_position] = 1;
	//�жϳ���
	if (now_position == width*height)
	{
		total_way_quantity++;
		/*cout << "��" << total_way_quantity << "��·:" << endl;
		vector<int>::iterator it;
		for (int i=0; i <cells_in_way.size(); i++)
		{
				cout <<cells_in_way[i]<< "  ";
		}*/
		return;//������һ��
	}
	for (int i = 0; i < 5; i++)
	{
		if (have_way[now_position][i] != 0 && book[have_way[now_position][i]]==0)//Ҫ���Եĵ㲻��·����
		{
			/*if (have_way[now_position][i] < cells_in_way[cells_in_way.size() - 1])
			{
				cells_in_way.pop_back();
			}*/
			book[now_position]= 1;//����Ѿ����Թ�
			find_best_way(have_way[now_position][i], set);//�Ҹ�cell��·
			if (total_way_quantity >=1)
			{
				return;
			}
			//cells_in_way.pop_back();
			book[have_way[now_position][i]] = 1;//����֮�󽫸õ�ȡ�����
			//cells_in_way[now_position] = 0;//��·���еĸõ�ȡ�����
		}	
		//&& != have_way[now_position][i]
	}

	book[now_position] = 0;//�õ���ĸ���������ϣ��������ء�
	//cells_in_way.pop_back();//�õ��Ѿ�����·�����ˡ���������������������
	if (have_way[now_position][2] == 0&&now_position!=width*height)
	{
		cells_in_way.pop_back();
	}
	return;
}
pair_cell Create_map::choose_two_cells()
{
	/*if (now_cell_quantity >= total_cell_quantity)
	{
		temp.pre = -2;
		temp.later = -2;
		return temp;
	}*/
	std::random_device rd;
	temp.pre = -1;
	temp.later = -1;
	int cell_select[4] = { 0 };
	int random_number=4;
	int loop = 0;
	//���������
	int cell_quantity = width*height;
	int temp2 = rd() % cell_quantity + 1;
	while (can_not_choose[temp2])
		{
			temp2 = (temp2 + 1) % (width*height + 1);
			if (temp2 == 0)
			{
				temp2 = 1;
			}
			loop++;                                                                        
			if (loop >= width*height)
			{
				temp.pre = -2;
				temp.later = -2;
				return temp;
			}
		}
	cell_selected_times[temp2]++;
	if (cell_selected_times[temp2] >= cell_max_selected_times[temp2])
	{
		can_not_choose[temp2] = 1;
	}
	int cell1 = temp2;//cell1һ���ǿ�ѡ��
	temp.pre = cell1;
	int cell2 = 0;
	//�м䲿�ֺ͵�һ�����һ�У����Ľǣ�
	cell_select[0] = cell1 - 1;
	cell_select[1] = cell1 + 1;
	cell_select[2] = cell1 + width;
	cell_select[3] = cell1 - width;
	if (cell1 == 1)
	{
		cell_select[0] = cell1 + width;
		//random_number = 2;
	}
	if (cell1 == width)
	{
		cell_select[1] = cell1 + width;
		//random_number = 2;
	}
	if (cell1 == width*height) //���Ͻ�
	{
		cell_select[1] = cell1 - width;
		//random_number = 2;
	}
	if (cell1 == (height - 1)*width + 1)//���Ͻ�
	{
		cell_select[0] = cell1 - width;
		//random_number = 2;
	}
	if (cell1 < width && cell1>1)//��һ��
	{
		//random_number = 3;
	}
	//���һ��
	if (cell1 > (height - 1)*width + 1 && cell1 < height*width)
	{
		cell_select[2] = cell1 - width;
		//random_number = 3;
	}
	//���һ��
	if (cell1%width == 1 && cell1 > width && cell1 < (height - 1)*width)
	{
		cell_select[0] = cell1 - width;
		//random_number = 3;
	}
	//�ұ�һ��
	if (cell1%width == 0 && cell1 != width &&cell1 != height*width)
	{
		cell_select[1] = cell1 - width; 
		//random_number = 3;
	}
	int aa = rd() % (cell_max_selected_times[cell1]);
	cell2 = cell_select[aa];
	for (int t = 0; t < cell_max_selected_times[cell1]; t++)//�ж���ǰ��ѡ��cell1���������ûͬʱѡ��cell2
	{
		if (head_temp[cell1][t] != cell2)
		{
			continue;
		}
		else//��ǰһ��ѡ������������ѡһ�����жϡ�������cell1û��������һ������cell2
		{
			while (1)
			{
				cell2 = cell_select[rd() % (cell_max_selected_times[cell1])];//����ѡһ����һ������ѡ����
				int reg = 0;//�����ж�cell
				for (int kk = 0; kk < cell_max_selected_times[cell1]; kk++)//���ж�
				{
					if (head_temp[cell1][kk] == cell2)
					{
						break;//��������ѡ
					}
					else
					{
						reg++;//����ȵĴ���
					}
				}
				if (reg == cell_max_selected_times[cell1])//ѡ����
				{
					break;
				}
			}
			break;//ѡ�������Ϳ���ֱ�ӷ�����
		}

	}
		//ѡ���˾����á�����Ȼ������һ����0
			for (int j = 0; j < cell_max_selected_times[cell1]; j++)
			{
				if (head_temp[cell1][j] == 0)
				{
					head_temp[cell1][j] = cell2;
					break;
				}
			}
	temp.later = cell2;
	for (int j = 0; j < cell_max_selected_times[cell2]; j++)
	{
		if (head_temp[cell2][j] == cell1)//���������������ǰ��ѡ������
		{
			return choose_two_cells();
		}
	}
	now_cell_quantity++;
	return temp;
}
int main(int argc, char** argv)
{
	GL_fun gl_fun;
	cout << "�������ͼ��͸ߣ�" << endl<<"�������"<<endl;
	cin >> width;
	cout << "������ߣ�" << endl;
	cin>>height;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1300,680);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Yapie.auto_mase");
	gl_fun.init();
	glutDisplayFunc(mydisplay);
	cout << "�����β";
	glutMainLoop();
}

