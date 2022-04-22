package 같은그림찾기;

import java.util.Random;

import javax.swing.ImageIcon;

public class GameReset {
	ImageIcon[] image;
	int [] arr;
	public GameReset() {
		// TODO Auto-generated constructor stub
		image=new ImageIcon[6];
		arr=new int[10];
	}
	public void imageFunction() {
		image[0]=new ImageIcon("images/01.jpg");
		image[1]=new ImageIcon("images/02.jpg");
		image[2]=new ImageIcon("images/03.jpg");
		image[3]=new ImageIcon("images/04.jpg");
		image[4]=new ImageIcon("images/05.jpg");
		image[5]=new ImageIcon("images/06.jpg");
	}
	public void randNumber()
	{
		int check=0;
		Random rand=new Random();
		for(int i=0;i<arr.length;i++)
		{
			arr[i]=rand.nextInt(5)+1;
			for(int x=0;x<i;x++)
			{
				if(arr[i]==arr[x])
					check++;
			}
			if(check==2)
			{
				check=0;
				i--;
				continue;
			}
			
			check=0;
		}
	}
	public int GetArr(int i) {
		return arr[i];
	}
	public ImageIcon GetImage(int i) {
		return image[i];
	}
}
