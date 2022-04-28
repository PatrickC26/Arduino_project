package tw.cgu.b0921251.midterm;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements

        //程式碼(A)   10% -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        View.OnLongClickListener,
        View.OnClickListener,
        CompoundButton.OnCheckedChangeListener,
        RadioGroup.OnCheckedChangeListener
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
{
    TextView txvB,txvD,txvP;
    View bg;
    Button btn;
    RadioGroup foodkind;
    int[] chk_id={R.id.chk1,R.id.chk2,R.id.chk3,R.id.chk4};
    String msg="";
    int B_price=0,D_price=0;    // B_price：點餐類型價錢；D_price：備註的價錢

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        txvB = (TextView) findViewById(R.id.txvB);
        txvD = (TextView) findViewById(R.id.txvD);
        txvP = (TextView) findViewById(R.id.txvP);
        bg = (View) findViewById(R.id.bg);
        btn = (Button) findViewById(R.id.btn);
        foodkind = (RadioGroup) findViewById(R.id.foodkind);

        //程式碼(B)   10% -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        foodkind.setOnCheckedChangeListener(this);
        for (int id : chk_id){
            CheckBox t = findViewById(id);
            t.setOnCheckedChangeListener(this);
        }
        btn.setOnLongClickListener(this);
        btn.setOnClickListener(this);
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    }

    @Override
    public void onCheckedChanged(RadioGroup group, int checkedId) {

        //程式碼(C)   20% -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        switch (group.getCheckedRadioButtonId()){
            case R.id.burger:
                B_price = 95;
                txvB.setText("您選的是Ｈ");
                break;
            case R.id.toast:
                B_price = 90;
                txvB.setText("您選的是Ｔ");
                break;
            case R.id.croissant:
                B_price = 100;
                txvB.setText("您選的是Ｃ");
                break;
        }
        showSum();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }

    //程式碼(D)   5% -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    void showSum(){
        txvP.setText("您的餐點價格為：NT$" + String.valueOf(B_price + D_price));
        CheckBox t = findViewById(R.id.chk1);
        if (B_price == 0 && D_price ==0 && !t.isChecked())
            msg = "請點餐";
        else if (D_price ==0 && !t.isChecked())
            msg = "您無特殊要求";

        txvD.setText(msg);
    }
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked){

        //程式碼(E)   30%-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        boolean dA = true;
        String tmsg = "您的特殊要求為：\n";;
        D_price = 0;

        for (int i = 0 ; i < 4 ; i++) {
            CheckBox t = findViewById(chk_id[i]);
            if (t.isChecked()) {
                dA = false;
                switch (i) {
                    case 0:
                        tmsg += "不加醃漬物(+0元)\n";
                        D_price += 0;
                        break;
                    case 1:
                        tmsg += "加肉(+20元)\n";
                        D_price += 20;
                        break;
                    case 2:
                        tmsg += "加歐姆蛋(+15元)\n";
                        D_price += 15;
                        break;
                    case 3:
                        tmsg += "加起司(+10元)\n";
                        D_price += 10;
                        break;
                }
            }
        }

        if (!dA)
            msg = tmsg.substring(0,tmsg.length()-1);

        showSum();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }

    @Override
    public void onClick(View v) {

        //程式碼(F)   10% -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        btn.setText("長按關");
        btn.setTextColor(Color.BLACK);
        bg.setBackgroundColor(Color.WHITE);
        for (int id : chk_id) {
            CheckBox t = findViewById(id);
            t.setVisibility(View.VISIBLE);
        }
        foodkind.setVisibility(View.VISIBLE);
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }

    @Override
    public boolean onLongClick(View v) {

        //程式碼(G)   15%-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        if (btn.getText().toString().contains("關")) {
            btn.setText("短按開");
            btn.setTextColor(Color.WHITE);
            bg.setBackgroundColor(Color.BLACK);
            foodkind.clearCheck();
            for (int id : chk_id) {
                CheckBox t = findViewById(id);
                t.setChecked(false);
                t.setVisibility(View.INVISIBLE);
            }
            foodkind.setVisibility(View.INVISIBLE);
            txvP.setText("您的餐點價格為：NT$");
            txvB.setText("您選的是");
            B_price = 0;
        }
        return true;
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    }
}