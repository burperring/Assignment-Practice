import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.BadLocationException;

public class JTextAreaSlider extends JFrame{
	private JTextArea ta = new JTextArea(5,20);
	private JSlider sd = new JSlider(JSlider.HORIZONTAL,0,100,0);
	
	public JTextAreaSlider() {
		setTitle("텍스트영역, 슬라이더 활용");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new BorderLayout());
		
		c.add(ta);
		c.add(sd, BorderLayout.SOUTH);
		
		sd.setPaintLabels(true);
		sd.setPaintTicks(true);
		sd.setPaintTrack(true);
		sd.setMajorTickSpacing(20);
		sd.setMinorTickSpacing(5);
		
		sd.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent e) {
				JSlider slider = (JSlider)e.getSource();
				if(ta.getText().length()<= slider.getValue()) {
					slider.setValue(ta.getText().length());
				}
				else {
					try {
						ta.setText(ta.getText(0,sd.getValue()));
					}catch(BadLocationException ex) {}
				}
			}
		});
		
		ta.addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent e) {
				JTextArea ta = (JTextArea)e.getSource();
				int size = ta.getText().length();
				try {
					if(size>=100)
						ta.setText(ta.getText(0,100));
				}catch(BadLocationException ex) {}
				sd.setValue(size);
			}
		});
		
		setSize(300,300);
		setVisible(true);
		
	}
	
	public static void main(String[] args) {
		new JTextAreaSlider();
	}
}
