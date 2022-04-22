package src.같은그림찾기;
/*
 * 클래스명 : GUI
 * 역활 : GUI관리
 */
import java.awt.GridLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class GUI {
	GameReset Game;
	//카드섞기,이미지 파일 불러오기,GUI 시작 
	public GUI() {
		// TODO Auto-generated constructor stub
		Game=new GameReset();
		Game.randNumber();
		Game.imageFunction();
		Start();
	}
	public void Start() {
		// TODO Auto-generated constructor stub
		JFrame frm=new JFrame("같은 그림 찾기");
		frm.setBounds(120, 120, 600, 300);
		
		JPanel bp=new JPanel();
		bp.setLayout(new GridLayout(2,5,4,4));
		cardButton[] btn=new cardButton[10];
		ActionButtonHandler action=new ActionButtonHandler(btn,this);
		for(int i=0;i<10;i++)
		{
			btn[i]=new cardButton(Integer.toString(i),Game.GetArr(i),Game.GetImage(Game.GetArr(i)),Game.GetImage(0));
			btn[i].addActionListener(action);
			bp.add(btn[i]);
		}
		
		
		frm.add(bp);
		frm.setVisible(true);
		frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
	}
	public int showPapUp() {
		int result;
		result=JOptionPane.showConfirmDialog(null,
				"계속하시겠습니까?","축하힙니다.",JOptionPane.YES_NO_OPTION);
		return result;
	}
	public GameReset ReturnGame() {
		return Game;
	}
}
