import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MouseListenerDrag extends JFrame{
	JPanel c = new JPanel(); //contentPane 지정
	
	public MouseListenerDrag()
	{
		setTitle("마우스 드래그시 화면색 변화 10-2실습문제");
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
