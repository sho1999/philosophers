/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:49:29 by smuramat          #+#    #+#             */
/*   Updated: 2022/08/28 21:30:33 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <libc.h>

typedef struct s_mutex
{
	int		cnt;
	pthread_mutex_t	mutex;

}					t_mutex;

void *routine(void *p)
{
	t_mutex *mu;
	mu = (t_mutex *)p;
	for (int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&mu->mutex); //lockして同時アクセスを防ぐ
		mu->cnt++;
		pthread_mutex_unlock(&mu->mutex);//ロック解除＝スレッドの２つ目（p2）の受付ができるようになる
	}
	return (NULL);
}

int main(void)
{
	pthread_t p1, p2;

	t_mutex *mu;
	mu = (t_mutex *)malloc(sizeof(t_mutex));
	mu->cnt = 0;
	
	/* mutex をデフォルト値に初期化する */
	pthread_mutex_init(&mu->mutex, NULL);

	// 2つのスレッドで並列処理する
	pthread_create(&p1, NULL, &routine, (void *)mu);
	pthread_create(&p2, NULL, &routine, (void *)mu);

	// 終了するまで待つ
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	
	//mutexの解放
	pthread_mutex_destroy(&mu->mutex);
	printf("cnt -> %d\n", mu->cnt);
}



// int cnt = 0;
// pthread_mutex_t mutex; //mutexを使うときに宣言

// void *routine(void *p)
// {
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		pthread_mutex_lock(&mutex); //lockして同時アクセスを防ぐ
// 		cnt++;
// 		pthread_mutex_unlock(&mutex);//ロック解除＝スレッドの２つ目（p2）の受付ができるようになる
// 	}
// 	return (NULL);
// }

// int main(void)
// {
// 	pthread_t p1, p2;
// 	pthread_mutex_t mutex; //mutexを使うときに宣言
// 	/* mutex をデフォルト値に初期化する */
// 	pthread_mutex_init(&mutex, NULL);


// 	// 2つのスレッドで並列処理する
// 	pthread_create(&p1, NULL, &routine, NULL);
// 	pthread_create(&p2, NULL, &routine, NULL);

// 	// 終了するまで待つ
// 	pthread_join(p1, NULL);
// 	pthread_join(p2, NULL);
	
// 	//mutexの解放
// 	pthread_mutex_destroy(&mutex);
// 	printf("cnt -> %d\n", cnt);
// }
