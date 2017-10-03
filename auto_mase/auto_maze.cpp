// auto_maze.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
using namespace std;
struct cell
{
	int cell_order;
	int rank;//深度
	int parent;
};

struct a_pair_cell//令pre<later
{
	int pre;
	int later;
};
// 按pre排列  
bool compare(const a_pair_cell &m1, const a_pair_cell &m2)
{
	return m1.pre < m2.pre;
}

typedef struct a_pair_cell pair_cell;
typedef struct cell ce;
int width,height,margin_left = 20, margin_bottom = 60, cell_width = 8,total_way_quantity=0;//放在全局区域避免重绘
class Set;
class Create_map
{
private:
	//friend class Set;
	static vector<pair_cell>barrier_across;//横线
	static vector<pair_cell>barrier_vertical;//竖线
	static vector<int>cells_in_way;
	pair_cell temp;
	int cell_quantity;
	int *first_select;//第一次选出来的那个的序号
	int **head_temp;
	int **have_way;//记录一个格子可以到达哪些点
	int *book;
	int *book_in_way;
	//static int *cells_in_way;
	int *cell_max_selected_times;
	int *cell_selected_times;//格子被选出来的次数
	int *can_not_choose;
	int total_cell_quantity;
	int now_cell_quantity;
	int step;//记录走了多少步
public:
	Create_map();
	void remove_barrier(ce &pre, ce &later,Set &set0);//拆墙
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
vector<pair_cell>  Create_map::barrier_across(init_across());//横线
vector<pair_cell>  Create_map::barrier_vertical(init_vertical());//竖线
int **Create_map::get_head_temp()
{
	return head_temp;
}
Create_map::Create_map()
{
	//total_way_quantity = 0;//当前没有路
	total_cell_quantity = (height - 2) * 6 + 4 + (height - 2)*(width - 2) * 2;
	now_cell_quantity = 0;
	cell_max_selected_times = new int[width*height + 1];
	cell_selected_times = new int[width*height + 1];
	book = new int[width*height + 1];
	head_temp = new int*[width*height+1];
	have_way = new int*[width*height + 1];
	first_select = new int[width*height+1];
	book_in_way = new int[width*height + 1];
	can_not_choose = new int[width*height + 1];//标记哪些格子不能再选了
	for (int i = 1; i <= width*height; i++)
	{
		book[i] = 0;
		can_not_choose[i] = 0;
		cell_selected_times[i] = 0;//被选次数初始化为0
		cell_max_selected_times[i] = 4;
		first_select[i] = 0;
		book_in_way[i] = 0;
		head_temp[i] = new int[5];
		have_way[i] = new int[5];
		if (i == 1 || i == width || i == (height - 1)*width + 1 || i == width*height)//四角
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
class Set//图由格子构成
{
private:
	ce *set;
	int quantity;//格子数量
	//int *remove;//拆除的墙
	//static Set set0;
public:
	Set(int m);//m是格子的数量
	ce find_set(int m);//寻找m的根节点
	bool check_finished();
	void union_set(int root1, int root2);//将两个连通集连成一个
	ce* get_set();
};//并查集
Set::Set(int m)//m是格子的数量
{
	quantity = m;
	set = (ce*)malloc((m + 1)*sizeof(ce));
	//remove = new int[quantity+1];//拆除的墙	
	set[0].cell_order = -10;
	set[0].parent = -10;
	set[0].rank = -10;
	for (int i = 1; i <= m; i++)
	{
		set[i].cell_order = i;
		set[i].parent = i;//表示都是单独的格子
		set[i].rank = 0;//树高都是0
						//remove[i] = -1;
	}
	
}
ce Set::find_set(int m)//寻找m的根节点

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
	//cout <<endl<< "尾部"<<set[width*height].parent;
	//cout << endl <<"开头 "<< set[1].parent;
	return true;
	
}
void Set::union_set(int root1, int root2)//将两个连通集连成一个
{
	if (root1 == root2)//i和j都是根，判断他们是不是同一个cell
	{
		return;
	}
	else
	{
		set[root1].parent = set[root2].cell_order;//没加rank
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
	if (m==n )//同一个连通集
	{
		return;
	}
	else//不同连通集
	{
		if (temp.later <= temp.pre)
		{
			cout << "尴尬了";
		}
		((temp.later - temp.pre) == width) ? barrier_across.push_back(temp) : barrier_vertical.push_back(temp);//压栈
		for (int i = 0; i < 5; i++)
		{
			if (have_way[temp.pre][i] == 0)
			{
				have_way[temp.pre][i] = temp.later;//故意这样设置，使得图是双向图
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
		set0.union_set(m,n);//联合
	}
}
void Create_map::handle_set()
{
	Set set0(width*height);
	Create_map map0;
	pair_cell cell;
	while (1)
	{
		ce* cell_temp = set0.get_set();//每执行一次就得重新获取一次
		cell.pre = -1;
		cell.later = -1;
		if (set0.check_finished())
		{
			break;
		}
		else
		{
			cell=map0.choose_two_cells();
			//cout << "选出来的" << cell.pre << "   " << cell.later << endl;
			map0.remove_barrier(cell_temp[cell.pre], cell_temp[cell.later],set0);
		}
	}
	//cout << "本应该" << endl;
	map0.find_best_way(1,set0);
//	map0.cells_in_way[1] = 1;
	map0.draw_map();
	for (int i = 1; i <= width*height; i++)
	{
		if (map0.have_way[i][4] != 0)
		{
			cout << map0.have_way[i][4] << "啊啊啊啊啊啊啊，最后一个错误";
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
	//cout << "出来了";
	int draw_across_times=width*(height-1);//分别计数需要的次数
	int draw_vertical_times=height*(width-1);
	int all_across_border=height+1;//边框
	int all_vertical_border=width+1;
	int temp=0;
	int temp1 = 0;
	vector<pair_cell>::iterator it;
	sort(barrier_across.begin(), barrier_across.end(), compare);//升序排列
	sort(barrier_vertical.begin(), barrier_vertical.end(), compare);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	//画网格
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
	
	//擦除标记的线
	glColor3f(0.0, 0.0, 0.0);
	//擦除横线
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
		}//temp指的是每一行从左往右数的第几个
		
		glBegin(GL_LINE_STRIP);
		glVertex2i(margin_left + cell_width*(temp -1), margin_bottom + ((it->pre) / width + temp1)*cell_width);
		glVertex2i(margin_left + cell_width*(temp), margin_bottom + ((it->pre) / width +temp1)*cell_width);
		glEnd();
	}
	//擦除竖线
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
	//擦除起始点和终止点
	glBegin(GL_LINE_STRIP);
	glVertex2i(margin_left, margin_bottom);
	glVertex2i(margin_left + cell_width, margin_bottom);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(margin_left + (width - 1)*cell_width, margin_bottom + height*cell_width);
	glVertex2i(margin_left + (width)*cell_width, margin_bottom + height*cell_width);
	glEnd();
	//画路线
	glColor3f(0.0, 0.0, 1.0);
	int i = 0, selected_cell1 = 1, selected_cell2 = 1;
	int j = 0;
	int first_time = 1;
	int circle_times = cells_in_way.size();
	int exchange = 0;
	if (circle_times == 0)
	{
		cout << "越界了";
		exit(0);
	}
	for (int k = 0; k < circle_times-1; k++)
	{
		if (abs(cells_in_way[k] - cells_in_way[k + 1]) != 1 && abs(cells_in_way[k] - cells_in_way[k + 1]) != width)
		{
			cout <<cells_in_way[k]<<"有问题!"<<"    ";
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
			//cout << "选出来的数:"<<selected_cell1 << "     " << selected_cell2 << endl;
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
			if (selected_cell2 - selected_cell1 == width)//竖线
			{
				glBegin(GL_LINE_STRIP);
				glVertex2i(margin_left+(temp-1)*cell_width+cell_width/2,margin_bottom+(temp1)*cell_width+cell_width/2);
				glVertex2i(margin_left+(temp - 1)*cell_width + cell_width / 2, margin_bottom + (temp1+1)*cell_width + cell_width / 2);
				glEnd();
			}
			if (selected_cell2 - selected_cell1 == 1)//横线
			{
				glBegin(GL_LINE_STRIP);
				glVertex2i(margin_left+(temp - 1)*cell_width + cell_width / 2, margin_bottom + (selected_cell1 / width)*cell_width+cell_width / 2);
				glVertex2i(margin_left+(temp)*cell_width + cell_width / 2, margin_bottom + (selected_cell1 / width)*cell_width + cell_width / 2);
				glEnd();
			}

		
	}
	cout << "画完了";
	//cout << "出阿来了！";
	
	glFlush();
}
void Create_map::find_best_way(int now_position,Set &set)
{
	//cout << now_position<<endl;
	//标记路径中的格子
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
		int t = cells_in_way[size - 2];//倒数第二个
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
					cout << endl << "找到了那个最讨厌的了" << cells_in_way[size1 - 4];
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
	//判断出口
	if (now_position == width*height)
	{
		total_way_quantity++;
		/*cout << "第" << total_way_quantity << "条路:" << endl;
		vector<int>::iterator it;
		for (int i=0; i <cells_in_way.size(); i++)
		{
				cout <<cells_in_way[i]<< "  ";
		}*/
		return;//返回上一步
	}
	for (int i = 0; i < 5; i++)
	{
		if (have_way[now_position][i] != 0 && book[have_way[now_position][i]]==0)//要尝试的点不在路径中
		{
			/*if (have_way[now_position][i] < cells_in_way[cells_in_way.size() - 1])
			{
				cells_in_way.pop_back();
			}*/
			book[now_position]= 1;//标记已经尝试过
			find_best_way(have_way[now_position][i], set);//找该cell的路
			if (total_way_quantity >=1)
			{
				return;
			}
			//cells_in_way.pop_back();
			book[have_way[now_position][i]] = 1;//返回之后将该点取消标记
			//cells_in_way[now_position] = 0;//将路径中的该点取消标记
		}	
		//&& != have_way[now_position][i]
	}

	book[now_position] = 0;//该点的四个方向尝试完毕，即将返回。
	//cells_in_way.pop_back();//该点已经不在路径中了。。。。。。可能有问题
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
	//生成随机数
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
	int cell1 = temp2;//cell1一定是可选的
	temp.pre = cell1;
	int cell2 = 0;
	//中间部分和第一行最后一行（除四角）
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
	if (cell1 == width*height) //右上角
	{
		cell_select[1] = cell1 - width;
		//random_number = 2;
	}
	if (cell1 == (height - 1)*width + 1)//左上角
	{
		cell_select[0] = cell1 - width;
		//random_number = 2;
	}
	if (cell1 < width && cell1>1)//第一行
	{
		//random_number = 3;
	}
	//最后一行
	if (cell1 > (height - 1)*width + 1 && cell1 < height*width)
	{
		cell_select[2] = cell1 - width;
		//random_number = 3;
	}
	//左边一行
	if (cell1%width == 1 && cell1 > width && cell1 < (height - 1)*width)
	{
		cell_select[0] = cell1 - width;
		//random_number = 3;
	}
	//右边一行
	if (cell1%width == 0 && cell1 != width &&cell1 != height*width)
	{
		cell_select[1] = cell1 - width; 
		//random_number = 3;
	}
	int aa = rd() % (cell_max_selected_times[cell1]);
	cell2 = cell_select[aa];
	for (int t = 0; t < cell_max_selected_times[cell1]; t++)//判断以前在选出cell1的情况下有没同时选出cell2
	{
		if (head_temp[cell1][t] != cell2)
		{
			continue;
		}
		else//以前一起选出来过。重新选一个再判断。。由于cell1没满，所以一定存在cell2
		{
			while (1)
			{
				cell2 = cell_select[rd() % (cell_max_selected_times[cell1])];//重新选一个。一定可以选出来
				int reg = 0;//用来判断cell
				for (int kk = 0; kk < cell_max_selected_times[cell1]; kk++)//再判断
				{
					if (head_temp[cell1][kk] == cell2)
					{
						break;//跳出重新选
					}
					else
					{
						reg++;//不相等的次数
					}
				}
				if (reg == cell_max_selected_times[cell1])//选好了
				{
					break;
				}
			}
			break;//选出来过就可以直接返回了
		}

	}
		//选好了就设置。。必然至少有一个是0
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
		if (head_temp[cell2][j] == cell1)//如果这两个数字以前被选出来过
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
	cout << "请输入地图宽和高：" << endl<<"请输入宽"<<endl;
	cin >> width;
	cout << "请输入高：" << endl;
	cin>>height;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1300,680);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Yapie.auto_mase");
	gl_fun.init();
	glutDisplayFunc(mydisplay);
	cout << "程序结尾";
	glutMainLoop();
}

