import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MouseListenerDrag extends JFrame{
	JPanel c = new JPanel(); //contentPane ����
	
	public MouseListenerDrag()
	{
		setTitle("���콺 �巡�׽� ȭ��� ��ȭ 10-2�ǽ�����");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(c);
		
		c.addMouseMotionListener(new MyMouseDrag());
		c.setBackground(Color.GREEN);
		setSize(300,250);
		setVisible(true);
	}
	
	public class MyMouseDrag implements MouseMotionListener
	{
		public void mouseDragged(MouseEvent e)
		{
			c = (JPanel)e.getSource();
			c.setBackground(Color.YELLOW);
		}
		public void mouseMoved(MouseEvent e)
		{
			c = (JPanel)e.getSource();
			c.setBackground(Color.GREEN);
		}
	}
	
	public static void main(String[] args)
	{
		new MouseListenerDrag();
	}
}
