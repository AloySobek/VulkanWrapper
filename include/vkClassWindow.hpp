/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkClassWindow.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:50:43 by vrichese          #+#    #+#             */
/*   Updated: 2019/12/02 17:22:31 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_WINDOW_HPP
# define VK_CLASS_WINDOW_HPP

# include "vkClassContainer.hpp"

class Window
{
	public:
		int mWidth;
		int	mHeight;
		GLFWwindow *mpWindow;

		Window() : mWidth(WIDTH), mHeight(HEIGHT)
		{
			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			mpWindow = glfwCreateWindow(mWidth, mHeight, "Vulkan", nullptr, nullptr);
		}

		void mainLoop(Vulkan vulkan)
		{
			while (!glfwWindowShouldClose(mpWindow))
			{
				glfwPollEvents();
				vulkan.vkDrawFrame();
			}
		}
};

#endif