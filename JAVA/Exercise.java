import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class MyPanel extends JPanel {
	private int x;
	private int y;
	private boolean flag = false;

	public MyPanel() {
		this.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent e) {
				flag = true;
				repaint();
			}
		});
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		if (flag == true) {
			g.setColor(Color.MAGENTA);
			x = (int) (Math.random() * this.getWidth() - 50);
			y = (int) (Math.random() * this.getHeight() - 50);
			g.drawOval(x, y, 50, 50);
		}
	}
}

class MyThread extends Thread {
	private MyPanel panel;

	public MyThread(MyPanel panel) {
		this.panel = panel;
	}

	public void run() {
		while (true) {
			panel.repaint();
			try {
				sleep(400);
			} catch (InterruptedException e) {
				return;
			}
		}
	}
}

public class Exercise extends JFrame {
	private MyPanel panel = new MyPanel();

	public Exercise() {
		setTitle("원을 0.5초 간격으로 생성하는 프로그램");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(panel);

		setSize(300, 300);
		setVisible(true);

		panel.setFocusable(true);
		panel.requestFocus();

		MyThread th = new MyThread(panel);
		th.start();
	}

	public static void main(String[] args) {
		new Exercise();
	}

}

