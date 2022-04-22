import javax.swing.*;

import java.awt.event.*;
import java.awt.*;

public class MouseListenerAllEx extends JFrame{
	private JLabel la = new JLabel("No Mouse Event");
	
	public MouseListenerAllEx()
	{
		setTitle("Mouse Listener�� MouseMotionListener ����");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Container c = getContentPane();
		c.setLayout(new FlowLayout());
		
		MyMouseListener listener = new MyMouseListener();
		c.addMouseListener(listener);
		c.addMouseMotionListener(listener);
		
		c.add(la);
		setSize(300,200);
		setVisible(true);
	}
	
	class MyMouseListener implements MouseListener, MouseMotionListener
	{
		// MouseListener�� 5�� �޼ҵ� ����
		public void mousePressed(MouseEvent e){
			la.setText("mousePressed ("+e.getX()+","+e.getY()+")");
		}
		public void mouseReleased(MouseEvent e){
			la.setText("mouseReleased("+e.getX()+","+e.getY()+")");
		}
		public void mouseClicked(MouseEvent e){
		}
		public void mouseEntered(MouseEvent e){
			Component c = (Component)e.getSource();
			c.setBackground(Color.CYAN);
		}
		public void mouseExited(MouseEvent e){
			Component c = (Component)e.getSource();
			c.setBackground(Color.YELLOW);
		}
		
		// MouseMotionListener�� 2�� �޼ҵ� ����
		public void mouseDragged(MouseEvent e){
			la.setText("mouseDragged ("+e.getX()+","+e.getY()+")");
		}
		public void mouseMoved(MouseEvent e){
			la.setText("mouseMoved   ("+e.getX()+","+e.getY()+")");
		}
	}
	
	public static void main(String[] args)
	{
		new MouseListenerAllEx();
	}
}
