package chap1;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;


public class Gui {
	Gameset Game;
	ImagePaenl imgP;
	//ī�弯��,�̹��� ���� �ҷ�����,GUI ���� 
	public Gui() {
		// TODO Auto-generated constructor stub
		Game=new Gameset();
		Game.randNumber();
		Game.imageFunction();
		Start();
	}
		public void Start() {
			JFrame frm=new JFrame("���� �׸� ã��");
			Container content=frm.getContentPane();
			
			
			imgP = new ImagePaenl();
			     
			content.add(imgP, BorderLayout.CENTER);
			   
			imgP.setLayout(new GridLayout(4,6));
			Cardbutton[] btn=new Cardbutton[24];
			AcionbuttonHandler action=new AcionbuttonHandler(btn,this);
			for(int i=0;i<24;i++)
			{
				btn[i]=new Cardbutton(Integer.toString(i),Game.GetArr(i),Game.GetImage(Game.GetArr(i)),Game.GetImage(0));
				btn[i].addActionListener(action);
				imgP.add(btn[i]);
			}
			
			
			frm.add(imgP);
			frm.setPreferredSize(new Dimension(800,950));
			frm.pack();
			frm.setVisible(true);
			frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		}
		public int showPapUp() {
			int result;
			result=JOptionPane.showConfirmDialog(null,
					"����Ͻðڽ��ϱ�?","�������ϴ�.",JOptionPane.YES_NO_OPTION);
			return result;
		}
		public Gameset ReturnGame() {
			return Game;
		}
	}