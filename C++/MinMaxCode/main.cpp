#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <iostream>
#include <string> 
#include <ctime>
#include <list>
#include "main.h"

using namespace std ;


int main(void) {


	node *root = new node ;	//root ��� ���� ��

	root->depth = 0;	//���� ��
	root->parent_move = NULL;

	node* tail = new _node;

		tail->sister_move = NULL;
		tail->parent_move = NULL;
		tail->headChild_move = NULL;

		root->sister_move = tail;

	spread();
	GenerateMoves(root);//��带 �����ϰ�.�ϴ� �ѹ���

	
	node* rootendNode = new node;
	rootendNode = get_endNode(root);//�ٴ��� ����Ű�� �ϰ�.
	
	MinMax(rootendNode->parent_move,-INFINITY,INFINITY);//�θƽ��� �����ϸ� ������ �ܰ踶�� �ƽ��� ���� ����.

	// int value = root->value;
	//	cout<<value<<endl;

return 0 ;
}

void MinMax(node *move , int alpha, int beta)
{
	node *p_move = new node;
	p_move = move;
	if( p_move==NULL)
	{	cout<< "��Ʈ�� �ƴѺκп��� ���� �߻�����";	
		return;
	}

	if ((move->depth)%2==0)
		MaxMove(p_move,alpha,beta);
	else
		MinMove(p_move,alpha,beta);

}

void MaxMove (node *move, int alpha, int beta) 
{

	int best_value = -INFINITY;
	
	int a , b;
	a = alpha;
	b = beta;

	node *c_node = move->headChild_move;
	
	if(c_node==NULL)//���̻� �ÿ����� �ʾƼ� ������忡 ã������ ������
	{
		node* endNode = new node;
		endNode = get_endNode(move->sister_move);//������� �ٴ��� ã��
		MinMax(endNode->parent_move,a,INFINITY);

	}


	cout<<"�ƽ��� ����"<<endl;
	
	int i = 0;
	
	while(c_node->sister_move!=NULL)
	{
		//cout<<i<<"th ��= " <<c_node->value<<"best : "<<best_value;
		//cout<<i<<"th �ּ�= " <<&c_node<<"  x_best : "<<best_value;
		cout<<c_node->depth<<"���� "<<i<</*"th �ּ�= " <<&c_node<<*/"  "<<i<<"��°���� : "<<  c_node->value;
		i++;
		if(c_node->value>best_value)
			best_value = c_node->value;
		if(c_node->value > b) //��Ÿ ������ ũ�� 
		{
			cout<<endl<<"//beta cutoff//"<<endl;
			break;
		}
		cout<<"   best : "<<best_value<<endl;

		c_node = c_node->sister_move;
	}

		move->value = best_value;//Ȯ��� ����� �ְ��� �����忡 �Է��Ѵ�.
		cout<<"�θ��� ���ð�"<<move->value<<endl;
		if(move->value<b)
		{
			b = move->value;
			cout<<"beta ��ü"<<endl;
		}
		cout<<"a:"<<a<<" b:"<<b<<endl<<endl;
		if(move->parent_move==NULL)
		{
			cout<<endl<<"root�� ���������� ���� ���� "<<move->value<<"�Դϴ�"<<endl;
			move->pos[0];
			return ;//exit(0);
		
		}
		else if (move->value < a)//���� ���ð��� ���ĺ��� ������ ���� �������� ���õǵ� ������ �ȵǹǷ� �׳� �θ� ��� ���� ���� ���� �ְ� 
		{
			cout<<"//����alpha cutoff//"<<endl;

			move->parent_move->value = move->value;//�θ� ��忡 ��� ���� �־��ְ� �θ���� ������ �ɷ���
			if(move->parent_move->sister_move->sister_move!=NULL)//���� ������ ������ �θƽ� 
			{
				node* endNode = new node;
				endNode = get_endNode(move->parent_move->sister_move);//������� �ٴ��� ã��
				MinMax(endNode->parent_move,a,INFINITY);
			}
			else if(move->parent_move->sister_move->sister_move==NULL)
				if (move->parent_move->parent_move!=NULL)
					MinMax(move->parent_move->parent_move,a,b);
				else
				{
					cout<<endl<<"root�� ���������� ���� ���� "<<move->value<<"�Դϴ�"<<endl;
					return ;
				}
		}

		else if(move->sister_move->sister_move!=NULL&&move->sister_move->headChild_move!=NULL)//���� ��尡 ���� �ƴϸ� 
		{	
				node* endNode = new node;
				endNode = get_endNode(move->sister_move);//������� �ٴ��� ã��
				MinMax(endNode->parent_move,-INFINITY,b);//�������� �θƽ� �Ҷ��� �ٴں��� ����
				//return;//�߰��� ���� ����
		}


		else if(move->sister_move->sister_move==NULL&&move->parent_move!=NULL)//���� ��尡 ���̸� (tail�̸�)���� �ö󰡼� �ش� �۾����� 
		{
			MinMax(move->parent_move,a,b);//���� �ö󰡼� �θƽ� �Ҷ� �İ���
			//return;//�߰��� ���� ����
		}
		
	return;

}


void MinMove (node *move, int alpha, int beta) 
{	
	int best_value = INFINITY;
	int a , b;
	a = alpha;
	b = beta;
	
	node *c_node = move->headChild_move;

	if(c_node==NULL)//���̻� �ÿ����� �ʾ� ������忡 ã������ ������
	{
		node* endNode = new node;
		endNode = get_endNode(move->sister_move);//������� �ٴ��� ã��
		MinMax(endNode->parent_move,a,INFINITY);

	}

	cout<<"���� ����"<<endl;
	
	int i = 0;
	
	while(c_node->sister_move!=NULL)//
	{
		//cout<<i<<"th ��= " <<c_node->value<<"best : "<<best_value;
		//cout<<i<<"th �ּ�= " << c_node<<"  x_best : "<<best_value;
		cout<<c_node->depth<<"���� "<<i<</*"th �ּ�= " <<&c_node<<*/"  "<<i<<"��°���� : "<<  c_node->value;
		i++;
		if(c_node->value<best_value)
			best_value = c_node->value;
		if(c_node->value < a) //
		{
			cout<<endl<<"//alpha cutoff//"<<endl;
			break;
		}
		cout<<"   best : "<<best_value<<endl;
		c_node = c_node->sister_move;
	}

		move->value = best_value;//Ȯ��� ����� �ְ��� �����忡 �Է��Ѵ�.
		cout<<"�θ��� ���ð�"<<move->value<<endl;
		if(move->value>a)
		{	
			a = move->value;
			cout<<"alpha ��ü"<<endl;
		}
		
		cout<<"a:"<<a<<" b:"<<b<<endl<<endl;

		if (move->value > b)//���� ���ð��� ���ĺ��� ������ ���� �������� ���õǵ� ������ �ȵǹǷ� �׳� �θ� ��� ���� ���� ���� �ְ� 
		{
			cout<<"//����beta cutoff//"<<endl;
			move->parent_move->value = move->value;//�θ� ��忡 ��� ���� �־��ְ� �θ���� ������ �ɷ���
			if(move->parent_move->sister_move->sister_move!=NULL)//���� ������ ������ �θƽ� 
			{
				node* endNode = new node;
				endNode = get_endNode(move->parent_move->sister_move);//������� �ٴ��� ã��
				MinMax(endNode->parent_move,-INFINITY,b);
			}
			else if(move->parent_move->sister_move->sister_move==NULL)
			{
				if (move->parent_move->parent_move!=NULL)
					MinMax(move->parent_move->parent_move,a,b);
				else
				{
					cout<<endl<<"root�� ���� ���� "<<move->value<<"�Դϴ�"<<endl;
	
					return ;
				}
			}
		}

		else if(move->sister_move->sister_move!=NULL&&move->sister_move->headChild_move!=NULL)//���� ��尡 ���� �ƴϸ� 
		{	
				node* endNode = new node;
				endNode = get_endNode(move->sister_move);//������� �ٴ��� ã��
				MinMax(endNode->parent_move,a,INFINITY);//�������� �θƽ� �Ҷ��� �ٴں��� ����
		}

		else if(move->sister_move->sister_move==NULL&&move->parent_move!=NULL)//���� ��尡 ���̸� (tail�̸�)���� �ö󰡼� �ش� �۾����� 
		{
			//���� �ö󰡼� �θƽ� �Ҷ� ����尡 ���̰� ���ܰ踦 ��� �������Ƿ�
			MinMax(move->parent_move,a,b);
		}
	
	return;

}


void GenerateMoves(node *p_move)//, const int& index, node *_move) {
{
	//spread();
	int index =rand() % 3+1; //1�������� 4���� ���� �� �����
	//if(index == 0)
	//{
	//	p_move->headChild_move=NULL;
	//	cout<<"3������ �Ѱ���";
	//	return;
	//}

	node *_move = new node[index];
	
	for (int i = 0 ; i <index ; i++)
	{	
		cout<<p_move->depth+1<<"-"<<i<<"th node  ";
		_move[i].depth = p_move->depth+1;

		_move[i].value = rand() % 20+1;//1���� 20���� ������ �� �Է�
		
	

		cout<< "value :"<<_move[i].value;//�Էµȼ� ���
		cout<<"  |  ";//������������ ������ ��
		_move[i].parent_move = p_move ; //�θ��� �ּ� �Է�
		cout<<"P_add:"<< _move[i].parent_move<<"  ";
		_move[i].headChild_move=NULL;

		if (i==0) // ù��° �İ� ����̸� �θ���� ã�ư� �ڱ� �ּҸ� �Է��ϰ� �ڽĳ�忡ptail �� ����. 
		{
			p_move->headChild_move = &_move[i];
			
			node* ptail = new _node;
			ptail->headChild_move = NULL;
			_move[i].sister_move = ptail;
			_move[i].headChild_move=NULL;

		}

		if (i ==index-1) //��������� �����̸� tail ����
		{
			node* tail = new _node;

			tail->sister_move = NULL;
			tail->parent_move = NULL;
			tail->headChild_move = NULL;

			_move[i].sister_move = tail;
			
		}

		else //������� �ּ� �Է�
		{
			_move[i].sister_move = &_move[i+1];

		}
		cout<<"M_add:"<< &_move[i]<<"  ";
		cout<<"S_add:"<< _move[i].sister_move<<"  ";
		cout<<endl;
	}
	if (p_move->depth<LIMIT)
	{
		//������ ���Ͽ� �ǻ����ֱ�
		for (int i = 0 ; i <index ; i++)
		{	
			GenerateMoves(&_move[i]);
		}
	}
}

node *get_endNode(node *move)// ���ϴ� ����� �ּҰ� ��ȯ�ϴ� �Լ�.
{
	node* endNode = new _node;
	endNode = move;
	while (endNode->headChild_move!=NULL)
	{
		endNode = endNode->headChild_move;
		cout<<"��ġ�� �ּ�:"<<endNode<<endl;
	}
	
		cout <<"��ȯ�� �ּ�:";
		cout<< endNode<<endl;
		return endNode;
	
}