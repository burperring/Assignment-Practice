import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

public class ImageMouseEvent extends JFrame{
	private MyPanel panel = new MyPanel();
	public ImageMouseEvent(){
		setTitle("이미지 위에 원 드래깅 연습");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(panel);
		setLayout(new FlowLayout());
		setSize(300, 300);
		setVisible(true);
	}
	
	// paintComponent를 이용하여 이미지 그림
	class MyPanel extends JPanel{
		private ImageIcon image = new ImageIcon("C:\\Users\\USER\\Pictures\\outside.jpg");
		private Image img = image.getImage();
		int x = 100, y = 100;
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			g.drawImage(img, 0, 0, getWidth(), getHeight(), this);		// 화면에 꽉 차게 설정
			g.setColor(Color.green);
			g.fillOval(x, y, 20, 20);								// 초기 위치는 (100, 100)으로 설정
			
			addMouseMotionListener(new MouseMotionAdapter() {
				public void mouseDragged(MouseEvent e) {
					// x와 y의 좌표를 드래그 된 위치로 바꾸고 repaint()
					x = e.getX();
					y = e.getY();
					repaint();
				}
			});
		}
	}
	
	public static void main(String[] args) {
		new ImageMouseEvent();
	}
}