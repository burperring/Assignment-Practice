import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

public class ImageMouseEvent extends JFrame{
	private MyPanel panel = new MyPanel();
	public ImageMouseEvent(){
		setTitle("�̹��� ���� �� �巡�� ����");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(panel);
		setLayout(new FlowLayout());
		setSize(300, 300);
		setVisible(true);
	}
	
	// paintComponent�� �̿��Ͽ� �̹��� �׸�
	class MyPanel extends JPanel{
		private ImageIcon image = new ImageIcon("C:\\Users\\USER\\Pictures\\outside.jpg");
		private Image img = image.getImage();
		int x = 100, y = 100;
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			g.drawImage(img, 0, 0, getWidth(), getHeight(), this);		// ȭ�鿡 �� ���� ����
			g.setColor(Color.green);
			g.fillOval(x, y, 20, 20);								// �ʱ� ��ġ�� (100, 100)���� ����
			
			addMouseMotionListener(new MouseMotionAdapter() {
				public void mouseDragged(MouseEvent e) {
					// x�� y�� ��ǥ�� �巡�� �� ��ġ�� �ٲٰ� repaint()
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