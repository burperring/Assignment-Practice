import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class KeyListenerEx extends JFrame{
	private JLabel[] keyMessage;
	
	public KeyListenerEx()
	{
		setTitle("keylistener 예제");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Container c = getContentPane();
		c.setLayout(new FlowLayout());
		c.addKeyListener(new MyKeyListener());
		
		// 레이블 배열을 3개 생성하고 각 레이블 컴포넌트 생성
		keyMessage = new JLabel[3];
		keyMessage[0] = new JLabel("getKeyCode()");
		keyMessage[1] = new JLabel("getKeyChar()");
		keyMessage[2] = new JLabel("getKeyText()");
		
		// 3개의 레이블 컴포넌트를 컨텐트팬에 부착
		for(int i = 0; i<keyMessage.length; i++)
		{
			c.add(keyMessage[i]);
			keyMessage[i].setOpaque(true);
			keyMessage[i].setBackground(Color.YELLOW);
		}
		
		setSize(300,150);
		setVisible(true);
		
		c.setFocusable(true);
		c.requestFocus();
	}
	
	// key 리스너 구현
	class MyKeyListener extends KeyAdapter
	{
		public void keyPressed(KeyEvent e)
		{
			int keyCode = e.getKeyCode();
			char keyChar = e.getKeyChar();
			keyMessage[0].setText(Integer.toString(keyCode));
			keyMessage[1].setText(Character.toString(keyChar));
			keyMessage[2].setText(KeyEvent.getKeyText(keyCode));
			
			System.out.println("KeyPressed");
		}
		
		public void keyReleased(KeyEvent e)
		{
			System.out.println("keyReleased");
		}
		
		public void keyTyped(KeyEvent e)
		{
			System.out.println("KeyTyped");
		}
	}
	
	public static void main(String[] args)
	{
		new KeyListenerEx();
	}
}
