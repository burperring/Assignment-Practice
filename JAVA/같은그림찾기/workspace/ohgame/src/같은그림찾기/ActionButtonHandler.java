package 같은그림찾기;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

public class ActionButtonHandler implements ActionListener {
	int i;
	cardButton[] btn;
	int[] arr;
	int check;
	int [] iArr;
	int score=0;
	GUI main;
	
	public ActionButtonHandler(cardButton[] button,GUI main) {
		// TODO Auto-generated constructor stub
		btn=button;
		arr=new int[2];
		check=0;
		iArr=new int[2];
		this.main=main;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		i=Integer.parseInt(e.getActionCommand());
		iArr[check]=i;
		arr[check]=btn[i].clickButton();
		
		if(arr[check]==-1)
			return;
		if(check==1)
		{
			if(arr[0]!=arr[1])
			{
				btn[iArr[0]].returnImage();
				btn[iArr[1]].returnImage();
			}
			else
			{
				score++;
				if(score==5)
				{
					int result=main.showPapUp();
					if(result==JOptionPane.YES_OPTION)
					{
						score=0;
						check=0;
						main.ReturnGame().randNumber();
						for(int i=0;i<10;i++)
						{
							btn[i].ChangeImage(main.ReturnGame().GetImage(main.ReturnGame().GetArr(i))
									,main.ReturnGame().GetArr(i));
							btn[i].returnImage();
						}
					}
					else
						System.exit(0);
				}
			}
			check=0;
			return;
			
		}
		check++;
		try {
			Thread.sleep((long)50);
		} 
		catch (InterruptedException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}
}
