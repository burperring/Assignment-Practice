
#define MAX 1
#define MIN 2
#define LIMIT 2//
//14������ ���� 16�ܰ� ���� �þ����� ���̴µ� 2��49�� ã�µ� 10�� ����.
//Ȯ���� ���� ���� 15������ ���� 17�ܰ���� �þ����� ���̴µ� 5�� 50�� ã�µ� 4�� ����.ã�½ð� 2�ʾ���.
#define spread() srand((unsigned)time(NULL))	//spead rand() ;


typedef struct _node{


	int see[LIMIT]; //������ ������ �ε����� �������� ��������. �ִ�  LIMIT ���� Ȯ���Ұ��̱⶧���� 10���� ������.
    //����� ũ�� ���� ���ؼ� x �� *100 y �� �״��
	//��ǥ �޾ƿͼ� ���� �Ѷ��� x �� 100���� ������ y �� 100���� ���� �������� ����Ѵ�.
	int value; // �ǿ� ���� ��ġ
	int depth; // ��� ���� : �ð������̳� ������ Ȯ���� �������� ���� ���� ��������. 
	struct _node *parent_move; //�θ� ��� �ּ�
	struct _node *sister_move; //���� ��� �ּ�
	struct _node *headChild_move; //�ڽ��� ù��° ��� �ּ�


}node;

void MinMax (node *move,int alpha, int beta);
void MaxMove(node *move,int alpha, int beta);
void MinMove(node *move,int alpha, int beta);
void GenerateMoves(node *p_move);//, const int& index, node *_move);

node *get_endNode(node *move);

static struct _node *endHeadNode=NULL;

static const int Random[10] = {12,4,9,5,2,16,13,18,7,9};
static int ran = 0;

static const int INFINITY = 1000000; 
