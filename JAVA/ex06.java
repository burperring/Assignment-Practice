import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class ex06 extends JFrame{
	
	JButton bt = new JButton("Calculate");
	JLabel lb = new JLabel("��� ��� ���");

	ex06(){
		
		Container c = getContentPane();
		c.setLayout(new FlowLayout());
		c.add(bt);
		c.add(lb);
		
		bt.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				calDialog cal = new calDialog();
				cal.setVisible(true);
			}
		});
		

		setTitle("������ ��α�");
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(300,300);
	}
	
	
	class calDialog extends JDialog{
		
		JTextField tf1 = new JTextField(10);
		JTextField tf2 = new JTextField(10);
		JButton bt = new JButton("ADD");
		calDialog(){
			setLayout(new FlowLayout());
			add(new JLabel("�� ���� ���մϴ�"));
			add(tf1);
			add(tf2);
			add(bt);
			
			setSize(100,200);
			setTitle("Calculation Dialog");
			
			bt.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					setVisible(false);
					
					int result = Integer.parseInt(tf1.getText()) + Integer.parseInt(tf2.getText());
					lb.setText(Integer.toString(result));
				}
			});
		}
	}
	
	public static void main(String[] args) {
		new ex06();
	}

}
?