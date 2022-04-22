import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class bbThread extends Thread{
	private JLabel la;
	private Container c;
	int x, y;
	public bbThread(Container c, JLabel la, int x, int y) {
		this.la = la;
		this.c = c;
		this.x = x;
		this.y = y;
	}
	
	public void run() {
		la.setLocation(x,y);
		c.add(la);
		while(true) {
			try {
				if(y>= -50) {
					y-=5;
					la.setLocation(x,y);
					sleep(20);
				}
				else if(y<-50)
					c.remove(la);
			}catch(InterruptedException e) {
				System.out.println("error");
			}
		}
	}
}

public class BubbleGame extends JFrame{
	JLabel la[] = new JLabel[40];
	ImageIcon bb_icon = new ImageIcon("C:\\Users\\USER\\Pictures\\bubble.jpg");
	bbThread bb[] = new bbThread[40];
	int i = 0;
	
	public BubbleGame() {
		super("버블 게임");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);
		setSize(700,700);
		setVisible(true);
		for(int i = 0; i<40; i++) {
			la[i] = new JLabel();
			la[i].setIcon(bb_icon);
			la[i].setSize(50,50);
		}
		
		c.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				bb[i] = new bbThread(c,la[i],e.getX(), e.getY());
				bb[i].start();
				i++;
			}
		});
		c.requestFocus();
	}
	
	public static void main(String[] args) {
		new BubbleGame();
	}
}

