/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 12:53:28 by lpieck            #+#    #+#             */
/*   Updated: 2026/06/18 14:53:52 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;

void render_frame(t_game *game);

#endif
