#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A) HW16A056 岸本 朋哉
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B) HW16A058 北田大河
// TODO: 砲台を青い壁に沿って上下に動かす。(C) HW16A058 北田大河
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D) HW16A058 北田大河
// TODO: スコアのサイズを大きくする。(E) HW16A195 峯村 玖礼人
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)HW16A195 峯村 玖礼人
// TODO: PlayBGM()関数を使って、BGMを再生する。(G) HW16A056 岸本 朋哉
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H) HW16A056 岸本 朋哉


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
int i = 1;


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-300, -150);
    targetRect = Rect(80, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
     PlayBGM("bgm_maoudamashii_8bit07.mp3");
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_system20.mp3");    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 10 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 1;         // スコアの加算
            PlaySound("se_maoudamashii_explosion03.mp3");
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
        }
        
        if(bulletPos.x > 310){
            bulletPos.x = -999;
        }

    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);
    
    cloudPos.x += 1;
    
    if(cloudPos.x >= 301){
        cloudPos.x -= 830;
    }


    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    cannonPos.y += 1 * i;
    if (cannonPos.y >= -60 ) {
        i *= -1;
    }
    if(cannonPos.y <= -150 ) {
        i *= -1;
    }

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 20.0f);
    DrawText(FormatString("%05d", score), Vector2(-319, 190), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-320, 190), Color::white);
}

