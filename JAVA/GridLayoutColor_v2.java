import java.awt.*;
import javax.swing.*;

public class GridLayoutColor extends JFrame {
	public GridLayoutColor()
	{
		setTitle("GridLayoutColor 실습9-4변형");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new GridLayout(1,10));
		
		JButton ColorButton[];
		for(int i = 0; i<10; i++)
		{
			ColorButton[i] = new JButton();
			add(ColorButton[i]);
		}
		ColorButton[0].setBackground(Color.RED);
		ColorButton[1].setBackground(Color.ORANGE);
		ColorButton[2].setBackground(Color.YELLOW);
		ColorButton[3].setBackground(Color.GREEN);
		ColorButton[4].setBackground(Color.CYAN);
		ColorButton[5].setBackground(Color.BLUE);
		ColorButton[6].setBackground(Color.MAGENTA);
		ColorButton[7].setBackground(Color.DARK_GRAY);
		ColorButton[8].setBackground(Color.PINK);
		ColorButton[9].setBackground(Color.GRAY);

		setSize(500,200);
		setVisible(true);
	}
	
	public static void main(String[] args)
	{
		new GridLayoutColor();
	}
}
