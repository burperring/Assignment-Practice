import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public class CheckBoxEvent extends JFrame{
	int[] unit = {50000,10000,1000,500,100,50,10,1};
	private JCheckBox [] moneycb = new JCheckBox[7];
	private String [] powerstr = {"금액","50000원","10000원"," 1000원","  500원","  100원","    50원","    10원","     1원"};
	private JTextField [] counttf = new JTextField[powerstr.length];
	private JButton btn = new JButton("계산");
	private JLabel la;
	
	public CheckBoxEvent() {
		setTitle("Money Changer");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setBackground(Color.PINK);
		c.setLayout(new FlowLayout());
		
		la = new JLabel(powerstr[0]);
		la.setSize(40,20);
		la.setLocation(30,20);
		c.add(la);
		
		counttf[0] = new JTextField(30);
		counttf[0].setSize(80,20);
		counttf[0].setLocation(90,20);
		c.add(counttf[0]);
		
		btn.setSize(70,20);
		btn.setLocation(200,20);
		btn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String input = counttf[0].getText();
				if(input.length() == 0)
					return;
				
				int money = Integer.parseInt(input);
				int m;
				
				for(int i = 0; i<unit.length; i++) {
					if(i == unit.length - 1) {
						m = money/unit[i];
						counttf[i+1].setText(Integer.toString(m));
						break;
					}
					if(!moneycb[i].isSelected()) {
						counttf[i+1].setText("0");
						continue;
					}
					
					m = money/unit[i];
					counttf[i + 1].setText(Integer.toString(m));
					if(m > 0)
						money = money % unit[i];
				}
			}
		});
		add(btn);
		
		for(int i = 1; i<powerstr.length;i++) {
			la = new JLabel(powerstr[i]);
			la.setHorizontalAlignment(JLabel.RIGHT);
			la.setSize(50,20);
			la.setLocation(50,50+(i*20));
			add(la);
			
			counttf[i] = new JTextField(30);
			counttf[i].setHorizontalAlignment(JTextField.CENTER);
			counttf[i].setSize(70,20);
			counttf[i].setLocation(120,50+(i*20));
			add(counttf[i]);
			
			if(i<powerstr.length - 1) {
				moneycb[i-1] = new JCheckBox();
				moneycb[i-1].setBackground(Color.PINK);
				moneycb[i-1].setSize(20,20);
				moneycb[i-1].setLocation(210,50+(i*20));
				add(moneycb[i-1]);
			}
		}
		
		setSize(430,300);
		setVisible(true);
		
	}
	
	public static void main(String[] args) {
		new CheckBoxEvent();
	}
}
