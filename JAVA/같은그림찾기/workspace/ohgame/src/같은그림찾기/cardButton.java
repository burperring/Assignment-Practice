package 같은그림찾기;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;

public class cardButton extends JButton {
	int num;
	ImageIcon image1,image2;
	boolean check;
	public cardButton(String str,int n,ImageIcon image,ImageIcon back) {
		// TODO Auto-generated constructor stub
		super(str,back);
		image1=image;
		image2=back;
		num=n;
		check=true;
	}
	public int clickButton() {
		if(check)
		{
			setIcon(image1);
			check=false;
			return num;
		}
		return -1;
	}
	public void  returnImage() {
		setIcon(image2);
		check=true;
	}
	public void ChangeImage(ImageIcon image,int n) {
		image1=image;
		num=n;
	}
}
