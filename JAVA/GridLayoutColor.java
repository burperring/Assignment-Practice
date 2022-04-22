import java.awt.*;
import javax.swing.*;

public class GridLayoutColor extends JFrame {
	public GridLayoutColor()
	{
		setTitle("GridLayoutColor ½Ç½À9-4");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new GridLayout(1,10));
		
		JButton b0,b1,b2,b3,b4,b5,b6,b7,b8,b9;
		b0 = new JButton("0");
		add(b0);
		b0.setBackground(Color.RED);
		b1 = new JButton("1");
		add(b1);
		b1.setBackground(Color.ORANGE);
		b2 = new JButton("2");
		add(b2);
		b2.setBackground(Color.YELLOW);
		b3 = new JButton("3");
		add(b3);
		b3.setBackground(Color.GREEN);
		b4 = new JButton("4");
		add(b4);
		b4.setBackground(Color.CYAN);
		b5 = new JButton("5");
		add(b5);
		b5.setBackground(Color.BLUE);
		b6 = new JButton("6");
		add(b6);
		b6.setBackground(Color.MAGENTA);
		b7 = new JButton("7");
		add(b7);
		b7.setBackground(Color.DARK_GRAY);
		b8 = new JButton("8");
		add(b8);
		b8.setBackground(Color.PINK);
		b9 = new JButton("9");
		add(b9);
		b9.setBackground(Color.GRAY);

		setSize(500,200);
		setVisible(true);
	}
	
	public static void main(String[] args)
	{
		new GridLayoutColor();
	}
}
