/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:42:52 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/27 13:48:48 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

int main(void)
{
	Triangle	app;

	try
	{
		app.run();
	}
	catch (const std::exception &error)
	{
		std::cout << "ERROR\n";
		std::cerr << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	return (0);
}